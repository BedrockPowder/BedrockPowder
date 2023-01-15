//
// Created by pepef on 24.07.2022.
//

#ifndef BEDROCKPOWDER_RAKNETHANDLER_HPP
#define BEDROCKPOWDER_RAKNETHANDLER_HPP

#include "Server/utils/StdEnv.h"

#include <sstream>

#include "Server/network/ProtocolInfo.h"
#include "Server/BedrockPowder.h"
#include "Server/utils/BinaryStream.hpp"

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include "Server/logger/Logger.hpp"
#include <stdlib.h>

#include <zlib.h>

#define ZLIB_DEFLATE_MODE 0
#define ZLIB_RAW_MODE 1
#define ZLIB_GZIP_MODE 2

typedef struct {
	Bytef* data;
	uLong size;
} zlib_buf_t;

class RakNetHandler {
public:
    RakNetHandler() = default;

    [[noreturn]]
    void init(int port, const std::string& ip_address, int max_players) {
        RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
        RakNet::SocketDescriptor descriptor(port, ip_address.c_str());

        if(peer->Startup(max_players, &descriptor, 1) == RakNet::RAKNET_STARTED) {
            peer->SetMaximumIncomingConnections(max_players);
            std::string message = compile_query_msg();

            message.insert(message.begin(), (signed char)message.size());
            message.insert(message.begin(), 0x00);

            peer->SetOfflinePingResponse(message.c_str(), message.size());

            while(true) {
                this->handle(peer);
            }
        }
    }

	// https://github.com/MFDGaming/CZlibHelper/blob/main/zlib_helper.h
	int zlib_decode(zlib_buf_t in, zlib_buf_t* out, int mode)
	{
		int status;
		int len = in.size;
		Bytef* uncomp = (Bytef*)malloc(len);
		uLong half_len = in.size / 2;

		if (in.size == 0) {
			return Z_OK;
		}

		z_stream stream;
		stream.next_in = in.data;
		stream.avail_in = in.size;
		stream.total_out = 0;
		stream.zalloc = Z_NULL;
		stream.zfree = Z_NULL;

		status = inflateInit2(
			&stream,
			mode == ZLIB_RAW_MODE ? -MAX_WBITS :
			mode == ZLIB_DEFLATE_MODE ? MAX_WBITS :
			mode == ZLIB_GZIP_MODE ? 16 + MAX_WBITS :
			MAX_WBITS
		);

		if (status != Z_OK) {
			return status;
		}

		do {
			if (stream.total_out >= len) {
				len += half_len;
				uncomp = (Bytef*)realloc(uncomp, len);
			}
			stream.next_out = (uncomp + stream.total_out);
			stream.avail_out = len - stream.total_out;
			status = inflate(&stream, Z_SYNC_FLUSH);
		} while (status == Z_OK);

		if (status != Z_STREAM_END) {
			return status;
		}

		out->size = stream.total_out;
		out->data = (Bytef*)malloc(stream.total_out);

		int i;
		for (i = 0; i < stream.total_out; ++i) {
			out->data[i] = uncomp[i];
		}

		free(uncomp);

		return inflateEnd(&stream);
	}

	int zlib_encode(zlib_buf_t in, zlib_buf_t* out, int level, int mode)
	{
		int status;
		out->size = compressBound(in.size);
		out->data = (Bytef*)malloc(out->size);

		z_stream stream;
		stream.next_in = in.data;
		stream.avail_in = in.size;
		stream.next_out = out->data;
		stream.avail_out = out->size;
		stream.zalloc = Z_NULL;
		stream.zfree = Z_NULL;

		status = deflateInit2(
			&stream,
			level,
			Z_DEFLATED,
			mode == ZLIB_RAW_MODE ? -MAX_WBITS :
			mode == ZLIB_DEFLATE_MODE ? MAX_WBITS :
			mode == ZLIB_GZIP_MODE ? 16 + MAX_WBITS :
			MAX_WBITS,
			9,
			Z_DEFAULT_STRATEGY
		);

		if (status != Z_OK) {
			return status;
		}

		status = deflate(&stream, Z_FINISH);

		if (status != Z_STREAM_END) {
			return status;
		}

		out->size = stream.total_out;

		return deflateEnd(&stream);
	}

    void handle(RakNet::RakPeerInterface *peer) {
        RakNet::Packet *packet;
        for(packet = peer->Receive(); packet; peer->DeallocatePacket(packet), packet = peer->Receive()) {
            BinaryStream* stream = new BinaryStream(packet->data, 0);
			stream->size = packet->bitSize;
			bool compressionEnabled = false;
			BinaryStream* streams = new BinaryStream(NULL);
			streams->size = 0;
			size_t streams_count = 0;
            switch(stream->get_unsigned_byte()) {
                // Minecraft packet
                case 0xFE: {
                    Logger::log("MCPE Game packet recieved.");
					stream->put_unsigned_byte(0xFE);
					stream->offset += stream->size;
					if (!compressionEnabled) {
						BinaryStream* data = new BinaryStream(NULL);
						data->buffer = (int8_t *)(Bytef*)(stream->buffer + 1);
						data->size = (uLong)(static_cast<size_t>(stream->size) - 1);
						data->offset = 0;
						do {
							BinaryStream* entry_stream = new BinaryStream(NULL);
							entry_stream->size = data->get_var_int();
							entry_stream->buffer = data->get_bytes(entry_stream->size);
							entry_stream->offset = 0;
							++streams_count;
							streams->buffer = entry_stream->buffer;
							streams = (BinaryStream*)realloc(streams, streams_count * sizeof(BinaryStream));
							if (streams->get_var_int() == 0xc1) { // request network settings
								streams->size = sizeof(streams);
								std::cout << "Player protocol version: " << streams->get_int_be();
								std::cout << std::endl;
								compressionEnabled = true;
							}
						} while(data->offset < data->size);
						free(data->buffer);
					}
					else {
						zlib_buf_t in;
						in.data = (Bytef*)(stream->buffer + 1);
						in.size = (uLong)(stream->size - 1);
						zlib_buf_t out;
						zlib_decode(in, &out, ZLIB_RAW_MODE);
						BinaryStream* data = new BinaryStream(NULL);
						data->buffer = (int8_t*)out.data;
						data->size = out.size;
						data->offset = 0;
						std::cout << "Compression reach" << std::endl;
					}
                    break;
                }
                // Catch New Incoming Connection.
                case 0x13: {
                    Logger::log("{} trying to connect.", {packet->systemAddress.ToString(true)});
                    break;
                }
                // Catch Disconnect.
                case 0x15: {
                    Logger::log("{} disconnected.", {packet->systemAddress.ToString(true)});
                    break;
                }
                // Catch Unconnected Ping.
                case 0x01: {
                    Logger::log("Server has pinged(from {}).", LogLevel::DEBUG, {packet->systemAddress.ToString(true)});
                    break;
                }
            }
        }
    }
};

#endif //BEDROCKPOWDER_RAKNETHANDLER_HPP
