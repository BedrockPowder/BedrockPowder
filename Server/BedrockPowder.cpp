//
// Created by pepef on 29.06.2022.
//

#include <chrono>

#include "BedrockPowder.h"
#include "command/defaults/StopCommand.h"
#include "command/defaults/HelpCommand.h"
#include "command/defaults/VersionCommand.h"

static CommandManager* command_manager;
static CommandOrigin* console;
static bool is_started = false;

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

    // Command related things.
    console = new CommandOrigin("console", false);
    command_manager = new CommandManager();
    command_manager->addCommand(new HelpCommand());
    command_manager->addCommand(new StopCommand());
    command_manager->addCommand(new VersionCommand());

    // Time from end point.
    auto ms_to = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    // Log time, that was consumed for start.
    Logger::log("Done! (" + to_string(ms_to.count() - ms_from.count()) + " ms)! For help type \"help\"");

    Logger::log("Running developer version.", LogLevel::NOTICE);

    // Server is waiting for console input.
    wait_for_command();
}

void BedrockPowder::shutdown() {
    Logger::log("Shutdown.");
    exit(6);
}