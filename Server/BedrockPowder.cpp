//
// Created by pepef on 29.06.2022.
//

#include "Server/BedrockPowder.h"

#include "Server/utils/StdEnv.h"

#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>

#include "Server/Constants.h"
#include "Server/logger/Logger.hpp"
#include "Server/utils/Utils.hpp"
#include "Server/actor/Console.hpp"
#include "Server/actor/player/Player.hpp"

static CommandManager* command_manager;
static CommandOrigin* console;
static LangConfiguration* lang_config;
static vector<class Player*> player_map;
static int max_players = 20;
static nlohmann::json config;

void wait_for_command() { // NOLINT(misc-no-recursion)
    string command;
    getline(cin, command);
    if(!command.empty()) {
        vector<string> split_cmdline = Utils::explode(command, ' ');
        vector<string> arguments;
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

void load_configuration() {
    string directory = Utils::getDirectory();
    std::ifstream read(directory + "\\server.json");
    if(!read) {
        Logger::log("Could not find \"server.json\". Creating new...", LogLevel::NOTICE);
        config["server_name"] = string(BEDROCKPOWDER_CORE_NAME) + " Server";
        config["lang"] = "en-us";
        config["debug_level"] = 0;
        config["max_players"] = 20;

        std::ofstream write(directory + "\\server.json");
        write << std::setw(4) << config << std::endl;
        return;
    }
    read >> config;
    Logger::log("Loaded server configuration successfully.");
}

bool BedrockPowder::isDebugMessagesEnabled() {
    int level;
    level = stoi(to_string(config["debug_level"]));
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

void BedrockPowder::start() {
    // Time from start point.
    auto ms_from = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    load_configuration();
    lang_config = new LangConfiguration(to_string(config["lang"]));
    lang_config->load();

    Logger::log("This server is running " + string(BEDROCKPOWDER_CORE_NAME) + " version " + string(BEDROCKPOWDER_VERSION));

    if(BedrockPowder::isDebugMessagesEnabled()) {
        Logger::log("Debug log enabled.");
    }
    if(BEDROCKPOWDER_IS_DEV) {
        Logger::log("You are running development version of " + string(BEDROCKPOWDER_CORE_NAME) + ".", LogLevel::WARN);
        Logger::log("Some features that implemented on development", LogLevel::WARN);
        Logger::log("version can be buggy and be unstable. Not RECOMMEND use it on Production.", LogLevel::WARN);
    }

    // Command related things.
    console = new CommandOrigin(new Console());
    command_manager = new CommandManager();
    command_manager->init();

    // Time from end point.
    auto ms_to = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    // Log time, that was consumed for start.
    Logger::log("Done! (" + to_string(ms_to.count() - ms_from.count()) + " ms)! For help type \"/help\"");

    // Command line is waiting for console input.
    wait_for_command();
}

void BedrockPowder::shutdown() {
    Logger::log("Shutdown.");
    system("pause");
    exit(6);
}