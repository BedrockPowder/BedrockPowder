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
    static void log(const string& message, enum LogLevel log_level = LogLevel::INFO) {
        int level = (int)log_level;
        string logger_title;
        switch (level) {
            case 0:
                logger_title = "[info]";
                break;
            case 1:
                logger_title = "[warn!]";
                break;
            case 2:
                logger_title = "[!error!]";
                break;
            case 3:
                logger_title = "[emergency!]";
                break;
            case 4:
                logger_title = "[notice!]";
                break;
            case 5:
                logger_title = "[debug]";
                break;
            default:
                logger_title = "[unknown.]";
        }
        if(level == 5 && !BedrockPowder::isDevMode()) {
            return;
        }
        stringstream logger_stream("");
        auto time_l = time(nullptr);
        logger_stream << "(" << std::put_time(localtime(&time_l), "%Y/%d %b - %H:%M:%S") << ")";
        logger_stream << logger_title;
        logger_stream << ": " << message.c_str() << endl;
        printf("%s", logger_stream.str().c_str());
    }
};

#endif //BEDROCKPOWDER_LOGGER_H
