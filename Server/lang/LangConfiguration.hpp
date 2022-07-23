//
// Created by pepef on 23.07.2022.
//

#ifndef BEDROCKPOWDER_LANGCONFIGURATION_HPP
#define BEDROCKPOWDER_LANGCONFIGURATION_HPP

#include "Server/utils/StdEnv.h"
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
        std::ifstream read(dir);
        if(!read) {
            this->config["unk_command_message"] = "Unknown command: {}. Use command /help to get all available commands.";
            //this->config[""] = "";
            std::ofstream write(dir);
            write << std::setw(4) << this->config << std::endl;
            return;
        }
        read >> this->config;
    }

    string getTranslatedString(const string& key) {
        string string_to_return;
        try {
            string_to_return = to_string(this->config[key]);
            string_to_return.erase(string_to_return.begin(), string_to_return.begin() + 1);
            string_to_return.pop_back();
        } catch (...) {
            string_to_return = "<no such key>(" + key + ")";
        }
        return string_to_return;
    }
private:
    nlohmann::json config;
    string current_code;
};

#endif //BEDROCKPOWDER_LANGCONFIGURATION_HPP
