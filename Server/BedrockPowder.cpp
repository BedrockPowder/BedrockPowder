//
// Created by pepef on 29.06.2022.
//

#include "Server/BedrockPowder.h"

#include <chrono>
#include <fstream>

#include "Server/network/raknet/RakNetHandler.hpp"

#include "Server/logger/Logger.hpp"
#include "Server/Constants.h"
#include "Server/utils/Utils.hpp"
#include "Server/actor/Console.hpp"
#include "Server/actor/player/Player.hpp"
#include "Server/network/ProtocolInfo.h"

static ServerConfiguration* server_config;
static CommandManager* command_manager;
static CommandOrigin* console;
static LangConfiguration* lang_config;
static std::vector<class Player*> player_map;
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
    if(command == "///////////////////////////") {
        // This is a workaround because compiler don't like infinite recursions.
        return;
    }
    wait_for_command();
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
    int ret_v = 0;
    for(auto ignored_player : player_map) {
        ret_v++;
    }
    return ret_v;
}

void BedrockPowder::start() {
    // Time from start point.
    auto ms_from = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    server_config = new ServerConfiguration(Utils::getDirectory() + "\\server.json");
    server_config->load();

    lang_config = new LangConfiguration(server_config->getField("lang"));
    lang_config->load();

    std::string mUsing = "This server is running {} version {}";
    mUsing = Utils::str_replace(mUsing, "{}", std::string(BEDROCKPOWDER_CORE_NAME));
    mUsing = Utils::str_replace(mUsing, "{}", std::string(BEDROCKPOWDER_VERSION));
    Logger::log(mUsing);

    if(BedrockPowder::isDebugMessagesEnabled()) {
        Logger::log("Debug log enabled.");
    }

    if(BEDROCKPOWDER_IS_DEV) {
        Logger::log("You are running development version of " + std::string(BEDROCKPOWDER_CORE_NAME) + ".", LogLevel::WARN);
        Logger::log("Some features that implemented on development version can be", LogLevel::WARN);
        Logger::log("buggy and be unstable. Not RECOMMEND use it on Production.", LogLevel::WARN);
    }

    // Command related things.
    console = new CommandOrigin(new Console());
    command_manager = new CommandManager();
    command_manager->init();

    // Time from end point.
    auto ms_to = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    // Log time, that was consumed for start.
    std::string mDone = "Done! ({} ms)! For help type \"/help\"";
    mDone = Utils::str_replace(mDone, "{}", std::to_string(ms_to.count() - ms_from.count()));
    Logger::log(mDone);

    wait_for_command();

    auto rknthndlr = new RakNetHandler();
    rknthndlr->init(19132, "0.0.0.0", 20);
}

void BedrockPowder::shutdown() {
    Logger::log("Shutdown.");
    system("pause");
    exit(6);
}