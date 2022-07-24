//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_LOGGER_H
#define BEDROCKPOWDER_LOGGER_H

#include <sstream>
#include <iomanip>

#include "Server/utils/StdEnv.h"

#include "Server/BedrockPowder.h"

enum LogLevel : int {
    INFO = 0,
    WARN = 1,
    ERROR_ = 2,
    EMERGENCY = 3,
    NOTICE = 4,
    DEBUG = 5,
};

class Logger {
public:
    static void log(const std::string& message, enum LogLevel log_level = LogLevel::INFO) {
        int level = (int)log_level;
        std::stringstream logger_stream("");

        auto current_time = time(nullptr);
        logger_stream << "(" << std::put_time(localtime(&current_time), "%Y/%d %b - %H:%M:%S") << ")";

        switch (level) {
            case 0:
                logger_stream << "[info]:";
                break;
            case 1:
                logger_stream << "[warn!]";
                break;
            case 2:
                logger_stream << "[!error!]:";
                break;
            case 3:
                logger_stream << "[emergency!]:";
                break;
            case 4:
                logger_stream << "[notice!]:";
                break;
            case 5:
                logger_stream << "[debug!]:";
                break;
            default:
                logger_stream << "[unknown.]";
        }
        if(level == 5 && !BedrockPowder::isDebugMessagesEnabled()) {
            return;
        }
        logger_stream << " " << message.c_str() << std::endl;
        printf("%s", logger_stream.str().c_str());
    }
};

#endif //BEDROCKPOWDER_LOGGER_H
