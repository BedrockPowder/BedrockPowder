//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_UTILS_HPP
#define BEDROCKPOWDER_UTILS_HPP

#include "Server/utils/StdEnv.h"

#include <sstream>
#include <vector>
#include <cstdio>
#include <direct.h>

class Utils {
public:
    static std::vector<std::string> explode(std::string const & target_string, char delimiter) {
        std::vector<std::string> result;
        std::istringstream iss(target_string);
        for (std::string token; getline(iss, token, delimiter); ) {
            result.push_back(move(token));
        }
        return result;
    }

    static std::string implode(const std::vector<std::string>& target, char delimiter) {
        std::string basicString;
        for (auto iter = target.begin(); iter != target.end(); ++iter) {
            basicString += (*iter);
            if (iter + 1 != target.end() ) {
                basicString += delimiter;
            }
        }
        return basicString;
    }

    static std::string str_replace(std::string& str, const std::string& from, const std::string& to) {
        size_t start_pos = str.find(from);
        if(start_pos == std::string::npos) {
            return str;
        }
        str.replace(start_pos, from.length(), to);
        return str;
    }

    static std::string getDirectory() {
        char dir_to_return[FILENAME_MAX];
        _getcwd(dir_to_return, sizeof(dir_to_return));
        return dir_to_return;
    }

    static std::string str_replace_a(std::string str, const std::string& from, const std::string& to) {
        size_t start_pos = 0;
        while((start_pos = str.find(from, start_pos)) != std::string::npos) {
            str.replace(start_pos, from.length(), to);
            start_pos += to.length();
        }
        return str;
    }
};

#endif //BEDROCKPOWDER_UTILS_HPP
