//
// Created by pepef on 26.07.2022.
//

#ifndef BEDROCKPOWDER_PACKETTYPE_HPP
#define BEDROCKPOWDER_PACKETTYPE_HPP

class ClientSide {};
class ServerSide {};
class AllSide : public ClientSide, public ServerSide {};

#endif //BEDROCKPOWDER_PACKETTYPE_HPP
