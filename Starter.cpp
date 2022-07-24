//
// Created by pepef on 22.07.2022.
//

#include "Server/BedrockPowder.h"

int main() {
    try {
        BedrockPowder::start();
    } catch (std::exception e) {
        std::cout << "Something went wrong.\n" << e.what() << std::endl;
        system("pause");
    }
}