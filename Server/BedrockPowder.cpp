//
// Created by pepef on 29.06.2022.
//

#include "Server/BedrockPowder.h"

#include "Server/Constants.h"
#include "Server/logger/Logger.hpp"
#include "Server/utils/Utils.hpp"
#include "Server/actor/Console.hpp"
#include "Server/command/defaults/StopCommand.h"
#include "Server/command/defaults/HelpCommand.h"
#include "Server/command/defaults/VersionCommand.h"
#include "Server/actor/player/Player.hpp"

#include <filesystem>

#include <nlohmann/json.hpp>

static CommandManager* command_manager;
static CommandOrigin* console;
static vector<class Player*> player_map;
static int max_players = 20;
static bool is_started = false;
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
        BedrockPowder::getCommandManager()->tryExecute(BedrockPowder::getConsoleOrigin(), split_cmdline[0], arguments);
    }
    wait_for_command();
}

#include <cstdio>
#include <direct.h>
#include <fstream>

void load_configuration() {
    char current_work_dir[FILENAME_MAX];
    _getcwd(current_work_dir, sizeof(current_work_dir));

    std::ifstream read(string(current_work_dir) + "\\server.json");
    if(!read) {
        Logger::log("Could not find \"server.json\". Creating new...", LogLevel::NOTICE);
        config["server_name"] = string(BEDROCKPOWDER_CORE_NAME) + " Server";
        config["debug_level"] = 0;
        config["max_players"] = 20;

        std::ofstream write(string(current_work_dir) + "\\server.json");
        write << std::setw(4) << config << std::endl;
        return;
    }
    read >> config;
    Logger::log("Loaded configuration successfully.");
}

bool BedrockPowder::isDevMode() {
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

void BedrockPowder::start() {
    if(is_started) {
        Logger::log("Another " + string(BEDROCKPOWDER_CORE_NAME) + " is running in this thread.");
        return;
    }
    is_started = true;
    // Time from start point.
    auto ms_from = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    Logger::log("This server is running " + string(BEDROCKPOWDER_CORE_NAME) + " version " + string(BEDROCKPOWDER_VERSION));

    Logger::log("Loading server configuration...");
    load_configuration();

    // Command related things.
    console = new CommandOrigin(new Console());
    command_manager = new CommandManager();
    command_manager->addCommand(new HelpCommand());
    command_manager->addCommand(new StopCommand());
    command_manager->addCommand(new VersionCommand());

    // Time from end point.
    auto ms_to = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    // Log time, that was consumed for start.
    Logger::log("Done! (" + to_string(ms_to.count() - ms_from.count()) + " ms)! For help type \"help\"");

    Logger::log("Running developer version.", LogLevel::NOTICE);


    Logger::log("ServerName: " + to_string(config["server_name"]), LogLevel::DEBUG);
    // Server is waiting for console input.
    wait_for_command();
}

void BedrockPowder::shutdown() {
    Logger::log("Shutdown.");
    exit(6);
}