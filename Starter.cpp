//
// Created by pepef on 22.07.2022.
//

#include <thread>
#include "Server/BedrockPowder.h"
#include <csignal>
#include "Server/logger/Logger.hpp"

void signal_handler(int signal) {
    if(signal == 2) {
        Logger::log("Recieved signal interrupt. Server will shutdown.");
        BedrockPowder::shutdown();
    }
}

int main() {
    signal(SIGINT, signal_handler);
    try {
        BedrockPowder::start();
    } catch (std::exception e) {
        Logger::log("Something went wrong.\nException output: {}", LogLevel::ERROR_, {e.what()});
        system("pause");
        exit(-6);
    }
}