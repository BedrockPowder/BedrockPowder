//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_LOGGER_H
#define BEDROCKPOWDER_LOGGER_H

#include <sstream>
#include <iomanip>

#include "Server/utils/StdEnv.h"
#include "Server/utils/MCTextFormat.h"

#include "Server/BedrockPowder.h"

enum LogLevel : int {
    INFO = 0, WARN = 1, ERROR_ = 2, EMERGENCY = 3, NOTICE = 4, DEBUG = 5,
};

static std::map<std::string, std::string> mcpecolors2console{{"§0", TEXTFORMAT_BLACK}, {"§1", TEXTFORMAT_DARK_BLUE}, {"§2", TEXTFORMAT_DARK_GREEN}, {"§3", TEXTFORMAT_DARK_AQUA}, {"§4", TEXTFORMAT_DARK_RED}, {"§5", TEXTFORMAT_DARK_PURPLE}, {"§6", TEXTFORMAT_GOLD}, {"§7", TEXTFORMAT_GRAY}, {"§8", TEXTFORMAT_DARK_GREY}, {"§9", TEXTFORMAT_BLUE}, {"§a", TEXTFORMAT_GREEN}, {"§b", TEXTFORMAT_AQUA}, {"§c", TEXTFORMAT_RED}, {"§d", TEXTFORMAT_LIGHT_PURPLE}, {"§e", TEXTFORMAT_YELLOW}, {"§f", TEXTFORMAT_WHITE}, {"§g", TEXTFORMAT_MINECOIN_GOLD}, {"§k", TEXTFORMAT_OBFUSCATED}, {"§l", TEXTFORMAT_BOLD}, {"§m", TEXTFORMAT_STRIKE_THROUGH}, {"§n", TEXTFORMAT_UNDERLINE}, {"§o", TEXTFORMAT_ITALIC}, {"§r", TEXTFORMAT_RESET}};

class Logger {
public:
    static void log(const std::string &message) {
        log(message, LogLevel::INFO, {});
    }

    static void log(const std::string &message, enum LogLevel log_level) {
        log(message, log_level, {});
    }

    static void log(const std::string &message, std::vector<std::string> args) {
        log(message, LogLevel::INFO, args);
    }

    static void log(const std::string &message, enum LogLevel log_level, std::vector<std::string> args) {
        int level = (int) log_level;
        std::string s;
        std::string format;
        switch(level) {
            case 0:
                format = TEXTFORMAT_BLUE;
                s = "INFO";
                break;
            case 1:
                format = TEXTFORMAT_YELLOW;
                s = "WARN";
                break;
            case 2:
                format = TEXTFORMAT_RED;
                s = "ERROR";
                break;
            case 3:
                format = TEXTFORMAT_DARK_RED;
                s = "EMERGENCY";
                break;
            case 4:
                format = TEXTFORMAT_YELLOW;
                s = "NOTICE";
                break;
            case 5:
                format = TEXTFORMAT_DARK_GREY;
                s = "DEBUG";
                break;
            default:
                format = TEXTFORMAT_DARK_GREY;
                s = "UNKNOWN";
        }
        std::string s2;
        if(level == 5 && !BedrockPowder::isDebugMessagesEnabled()) {
            s2 = TEXTFORMAT_GRAY;
            return;
        }
        std::stringstream timestream("");
        auto current_time = time(nullptr);
        std::string end_message = message;
        for(auto pair : mcpecolors2console) {
            end_message = Utils::str_replace_a(end_message, pair.first, pair.second);
        }
        for(auto ssss : args) {
            end_message = Utils::str_replace(end_message, "{}", ssss);
        }
        std::stringstream logger("");
        logger << TEXTFORMAT_GRAY << "[" << std::put_time(localtime(&current_time), "%d %b - %H:%M:%S") << "]" << TEXTFORMAT_RESET << format << " [" << s << "]" << TEXTFORMAT_RESET << "> " << s2 << end_message << TEXTFORMAT_RESET << std::endl;
        printf("%s", logger.str().c_str());
    }
};

#endif //BEDROCKPOWDER_LOGGER_H
