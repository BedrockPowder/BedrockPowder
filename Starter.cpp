//
// Created by pepef on 22.07.2022.
//

#include "Server/BedrockPowder.h"

int main() {
    try {
        BedrockPowder::start();
    } catch (...) {
        cerr << "Something went wrong." << endl;
        system("pause");
    }
}