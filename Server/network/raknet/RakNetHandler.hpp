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
			   data->buffer = (int8_t *)(stream->buffer + 1);
			   data->size = (static_cast<size_t>(stream->size) - 1);
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
					   std::cout << "Player protocol version: " << streams->get_int_be();
					   std::cout << std::endl;
					   compressionEnabled = true;
					   free((void *)streams->buffer);
				   }
			   } while(data->offset < data->size);
		    } else {
			std::cout << "Compression reach" << std::endl;
			//todo: got a better idea on what to do
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
