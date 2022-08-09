//
// Created by pepef on 29.06.2022.
//

#include "Server/BedrockPowder.h"

#include <thread>
#include <chrono>
#include <fstream>

#include "Server/network/raknet/RakNetHandler.hpp"

#include "Server/logger/Logger.hpp"
#include "Server/Constants.h"
#include "Server/utils/Utils.hpp"
#include "Server/actor/Console.hpp"
#include "Server/network/ProtocolInfo.h"
#include "Server/network/pstorage/PacketStorage.hpp"
#include "Server/network/packets/LoginPacket.hpp"
#include "Server/network/packets/PlayStatusPacket.hpp"

static ServerConfiguration* server_config;
static CommandManager* command_manager;
static CommandOrigin* console;
static LangConfiguration* lang_config;
static PacketStorage* packet_store;
static std::vector<class Player*> player_map{};
static int max_players = 20;

void wait_for_command() { // NOLINT(misc-no-recursion)
    std::string command;
    std::cin.clear();
    getline(std::cin, command);
    if(!command.empty()) {
        std::vector<std::string> split_cmdline = Utils::explode(command, ' ');
        std::vector<std::string> arguments;
        if(split_cmdline.size() == 1) {
            arguments = {};
        } else {
            bool is_first_passed = false;
            for(const auto& arg : split_cmdline) {
                if(!is_first_passed) {
                    is_first_passed = true;
                    continue;
                }
                arguments.push_back(arg);
            }
        }
        BedrockPowder::getCommandManager()->handleCommandRequest(BedrockPowder::getConsoleOrigin(), split_cmdline[0], arguments);
    }
    wait_for_command();
}

std::vector<Player*> BedrockPowder::getAllPlayers() {
    return player_map;
}

bool BedrockPowder::isDebugMessagesEnabled() {
    int level;
    level = stoi(server_config->getField("debug_level"));
    return level != 0;
}

class CommandManager* BedrockPowder::getCommandManager() {
    return command_manager;
}

class CommandOrigin* BedrockPowder::getConsoleOrigin() {
    return console;
}

class LangConfiguration* BedrockPowder::getLangConfig() {
    return lang_config;
}

class ServerConfiguration* BedrockPowder::getServerConfig() {
    return server_config;
}

class PacketStorage* BedrockPowder::getPacketStorage() {
    return packet_store;
}

std::string compile_query_msg() {
    std::string mQueryMessage = "{};{};{};{};{};{};{};{};{};{};{};{};";
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", GAME_NAME);
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", BedrockPowder::getServerConfig()->getField("server_name"));
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", std::to_string(PROTOCOL_VERSION));
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", MCPE_VERSION);
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", std::to_string(BedrockPowder::getOnlinePlayers()));
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", BedrockPowder::getServerConfig()->getField("max_players"));
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", "0");
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", "BedrockPowder");
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", "Survival");
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", "1");
    mQueryMessage = Utils::str_replace(mQueryMessage, "{}", BedrockPowder::getServerConfig()->getField("server_port"));
    //mQueryMessage = Utils::str_replace(mQueryMessage, "{}", "200");
    return mQueryMessage;
}

int BedrockPowder::getOnlinePlayers() {
    return player_map.size();
}

#include <ppl.h>

void BedrockPowder::start() {
#ifdef _WIN32
    system("chcp 1251");
#endif // _WIN32
    // Time from start point.
    auto ms_from = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    server_config = new ServerConfiguration(Utils::getDirectory() + "\\server.json");
    server_config->load();

    lang_config = new LangConfiguration(server_config->getField("lang"));
    lang_config->load();

    Logger::log("This server is running {} version {}", {std::string(BEDROCKPOWDER_CORE_NAME), std::string(BEDROCKPOWDER_VERSION)});

    if(BedrockPowder::isDebugMessagesEnabled()) {
        Logger::log("Debug log enabled.");
    }

    //BinaryStream* s = new BinaryStream();
    //s->put_byte(1);

    packet_store = new PacketStorage();
    packet_store->registerPacket(new LoginPacket());
    packet_store->registerPacket(new PlayStatusPacket());

    if(BEDROCKPOWDER_IS_DEV) {
        Logger::log("You are running development version of {}.", LogLevel::WARN, {std::string(BEDROCKPOWDER_CORE_NAME)});
        Logger::log("Some features that implemented on development version can be", LogLevel::WARN);
        Logger::log("buggy and be unstable. Not RECOMMEND use it on Production.", LogLevel::WARN);
    }

    // Command related things.
    console = new CommandOrigin(new Console("server", false));
    command_manager = new CommandManager();
    command_manager->init();

    // Time from end point.
    auto ms_to = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    // Log time, that was consumed for start.
    Logger::log("Done! ({} ms)! For help type \"help\"",{std::to_string(ms_to.count() - ms_from.count())});

    concurrency::parallel_invoke(
            [](){
                std::thread command_thread(wait_for_command);
                command_thread.join();
                },
            [](){
                auto rknthndlr = new RakNetHandler();
                rknthndlr->init(std::stoi(server_config->getField("server_port")), server_config->getField("server_ip"), max_players);
            }
            );
}

void BedrockPowder::shutdown() {
    Logger::log("Shutdown.");
    exit(6);
}