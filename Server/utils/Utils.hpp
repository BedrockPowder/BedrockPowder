//
// Created by pepef on 22.07.2022.
//

#ifndef BEDROCKPOWDER_UTILS_HPP
#define BEDROCKPOWDER_UTILS_HPP

#include <iostream>
#include <sstream>
#include <vector>

class Utils {
public:
    static std::vector<std::string> explode(std::string const & target_string, char delimiter) {
        std::vector<std::string> result;
        std::istringstream iss(target_string);
        for (std::string token; std::getline(iss, token, delimiter); ) {
            result.push_back(std::move(token));
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
};

#endif //BEDROCKPOWDER_UTILS_HPP
