//
// Created by pepef on 24.07.2022.
//

#ifndef BEDROCKPOWDER_PROTOCOLINFO_H
#define BEDROCKPOWDER_PROTOCOLINFO_H

#include "Server/utils/StdEnv.h"

#define MCPE_VERSION "1.19.11.01"
#define GAME_NAME "MCPE"
#define PROTOCOL_VERSION 534

// todo: automate.
enum PacketIDs : int {
    login_packet = 0x01,
    play_status_packet = 0x02,
    server_to_client_handshake_packet = 0x03,
    client_to_server_handshake_packet = 0x04,
    disconnect_packet = 0x05,
    resource_packs_info_packet = 0x06,
    resource_pack_stack_packet = 0x07,
    resource_pack_client_response_packet = 0x08,
    text_packet = 0x09,
    set_time_packet = 0x0a,
    start_game_packet = 0x0b,
    add_player_packet = 0x0c,
    add_actor_packet = 0x0d,
    remove_actor_packet = 0x0e,
    add_item_actor_packet = 0x0f,
};

#endif //BEDROCKPOWDER_PROTOCOLINFO_H
