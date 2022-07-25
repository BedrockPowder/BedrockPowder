//
// Created by pepef on 22.07.2022.
//

#include <thread>
#include "Server/BedrockPowder.h"

int main() {
    try {
        std::thread thread(BedrockPowder::start);
        thread.join();
    } catch (std::exception e) {
        std::cout << "Something went wrong.\n" << e.what() << std::endl;
        system("pause");
    }
}