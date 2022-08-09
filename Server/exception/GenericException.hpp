//
// Created by pepef on 09.08.2022.
//

#ifndef BEDROCKPOWDER_GENERICEXCEPTION_HPP
#define BEDROCKPOWDER_GENERICEXCEPTION_HPP

#include <utility>

#include "Server/utils/StdEnv.h"

class GenericException : public std::exception {
public:
    explicit GenericException(std::string comment) {
        this->comment = std::move(comment);
    }

    std::string what() {
        return this->comment;
    }

private:
    std::string comment;
};

#endif //BEDROCKPOWDER_GENERICEXCEPTION_HPP
