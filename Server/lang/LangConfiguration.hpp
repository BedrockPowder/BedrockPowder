//
// Created by pepef on 23.07.2022.
//

#ifndef BEDROCKPOWDER_LANGCONFIGURATION_HPP
#define BEDROCKPOWDER_LANGCONFIGURATION_HPP

#include "Server/utils/StdEnv.h"
//#include "Server/logger/Logger.hpp"
#include "Server/utils/Utils.hpp"
#include "Server/Constants.h"
#include <nlohmann/json.hpp>
#include <fstream>

class LangConfiguration {
public:
    explicit LangConfiguration(string code) {
        string code_t = Utils::str_replace(code, "\"", "");
        code_t = Utils::str_replace(code_t, "\"", "");
        this->current_code = std::move(code_t);
    }

    void load() {
        string dir = Utils::getDirectory();
        dir += "\\lang";
        if(!std::filesystem::exists(dir)) {
            std::filesystem::create_directories(dir);
        }

        dir += "\\" + this->current_code + ".json";
        cerr << "a" << endl;
        std::ifstream read(dir);
        cerr << dir << endl;
        if(!read) {
            //Logger::log("Could not find \"lang\\" + this->current_code + ".json\". Creating new...", LogLevel::NOTICE);
            cerr << "c" << endl;
            config["unk_command_message"] = "Unknown command: {}. Use command /help to get all available commands.";
            cerr << "d" << endl;
            std::ofstream write(dir);
            write << std::setw(4) << this->config << std::endl;
            return;
        }
        cerr << "e" << endl;
        read >> this->config;
        cerr << "f" << endl;
        //Logger::log("Loaded configuration successfully.");
    }

    string getTranslatedString(const string& key) {
        string string_to_return;
        try {
            string_to_return = to_string(this->config[key]);
        } catch (...) {
            string_to_return = "<no such key>(" + key + ")";
        }
        string_to_return = Utils::str_replace(string_to_return, "\"", "");
        string_to_return = Utils::str_replace(string_to_return, "\"", "");
        return string_to_return;
    }
private:
    nlohmann::json config;
    string current_code;
};

#endif //BEDROCKPOWDER_LANGCONFIGURATION_HPP
