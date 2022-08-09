//
// Created by pepef on 09.08.2022.
//

#ifndef BEDROCKPOWDER_PLAYSTATUSPACKET_HPP
#define BEDROCKPOWDER_PLAYSTATUSPACKET_HPP

#include "Server/utils/StdEnv.h"
#include "Server/network/PacketType.hpp"
#include "Server/network/MCPEPacket.hpp"
#include "Server/network/ProtocolInfo.h"

enum class PlayStatus : uint32_t {
    login_success,
    login_failed_client,
    login_failed_server,
    player_spawn,
    login_failed_invalid_tenant,
    login_failed_vanilla_edu,
    login_failed_edu_vanilla,
    login_failed_server_full,
    login_failed_editor_vanilla,
    login_failed_vanilla_editor,
    };

class PlayStatusPacket : public MCPEPacket<ServerSide> {
public:
    PlayStatusPacket() : MCPEPacket<ServerSide>(PacketIDs::play_status_packet) {}

    explicit PlayStatusPacket(enum class PlayStatus status) : MCPEPacket<ServerSide>(PacketIDs::play_status_packet) {
        this->status = (uint32_t)status;
    }

    void read(BinaryStream* binaryStream) override {
        this->status = binaryStream->get_var_int();
    }

    void write(BinaryStream* binaryStream) override {
        binaryStream->put_var_int(this->status);
    }

protected:
    uint32_t status{};
};

#endif //BEDROCKPOWDER_PLAYSTATUSPACKET_HPP
