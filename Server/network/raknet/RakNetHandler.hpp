//
// Created by pepef on 24.07.2022.
//

#ifndef BEDROCKPOWDER_RAKNETHANDLER_HPP
#define BEDROCKPOWDER_RAKNETHANDLER_HPP

#include "Server/utils/StdEnv.h"

#include <sstream>

#include "Server/network/ProtocolInfo.h"
#include "Server/BedrockPowder.h"

#include <RakPeerInterface.h>
#include <RakNetTypes.h>
#include <BitStream.h>
#include "Server/logger/Logger.hpp"

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
            switch(packet->data[0]) {
                // Catch encrypted(?) encapsulated MCPE Packet.
                // So now I dont know is packets encrypted @see(?) https://wiki.vg/Raknet_Protocol#Open_Connection_Request_2
                case 0xFE: {
                    Logger::log("MCPE Game packet recieved.");
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
