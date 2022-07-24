//
// Created by pepef on 24.07.2022.
//

#ifndef BEDROCKPOWDER_RAKNETHANDLER_HPP
#define BEDROCKPOWDER_RAKNETHANDLER_HPP

#include "Server/utils/StdEnv.h"

#include <sstream>

#include "Server/network/ProtocolInfo.h"
#include "Server/BedrockPowder.h"

#include "RakPeerInterface.h"
#include "RakNetTypes.h"
#include "BitStream.h"

class RakNetHandler {
public:
    RakNetHandler() = default;

    [[noreturn]]
    void init(int port, const std::string& ip_address, int max_players) {
        RakNet::RakPeerInterface *peer = RakNet::RakPeerInterface::GetInstance();
        RakNet::SocketDescriptor descriptor(port, ip_address.c_str());

        if(peer->Startup(max_players, &descriptor, 1) == RakNet::RAKNET_STARTED) {
            peer->SetMaximumIncomingConnections(max_players);
            std::ostringstream motd;
            motd << compile_query_msg();
            std::string message = motd.str();

            // Adding size of packet
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
            //printf("[packetName(%c)]data: %s\n", packet->data[0], packet->data);
            switch(packet->data[0]) {
                case 0xFE: {
                    RakNet::BitStream stream(packet->data, packet->length, false);
                    stream.IgnoreBytes(sizeof(RakNet::MessageID));
                    int length;
                    stream.Read(length);
                    break;
                }
            }
        }
    }
};

#endif //BEDROCKPOWDER_RAKNETHANDLER_HPP
