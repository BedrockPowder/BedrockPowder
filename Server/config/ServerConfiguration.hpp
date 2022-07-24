//
// Created by pepef on 24.07.2022.
//

#ifndef BEDROCKPOWDER_SERVERCONFIGURATION_HPP
#define BEDROCKPOWDER_SERVERCONFIGURATION_HPP

#include <nlohmann/json.hpp>
#include "Server/utils/StdEnv.h"

class ServerConfiguration {
public:
    explicit ServerConfiguration(const std::string& path) {
        this->c_path = path;
    }

    void load() {
        std::ifstream read(this->c_path);
        if(!read) {
            this->json_storage["server_name"] = std::string(BEDROCKPOWDER_CORE_NAME) + " Server";
            this->json_storage["server_ip"] = "0.0.0.0";
            this->json_storage["server_port"] = "19132";
            //this->json_storage["server_ip"] = "";
            this->json_storage["lang"] = "en-us";
            this->json_storage["debug_level"] = 0;
            this->json_storage["max_players"] = 20;

            std::ofstream write(this->c_path);
            write << std::setw(4) << this->json_storage << std::endl;
            return;
        }
        read >> this->json_storage;
    }

    std::string getField(const std::string& field) {
        std::string string_to_return;
        try {
            string_to_return = to_string(this->json_storage[field]);
            if(field != "debug_level" && field != "max_players") {
                string_to_return.erase(string_to_return.begin(), string_to_return.begin() + 1);
                string_to_return.pop_back();
            }
        } catch (...) {
            string_to_return = "<no such field>(" + field + ")";
        }
        return string_to_return;
    }
private:
    nlohmann::json json_storage;
    std::string c_path;
};

#endif //BEDROCKPOWDER_SERVERCONFIGURATION_HPP
