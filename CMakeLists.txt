cmake_minimum_required(VERSION 3.22)
project(BedrockPowder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

set(BedrockPowder_src
        Server/BedrockPowder.cpp
        Server/BedrockPowder.h
        Server/Constants.h
        Server/logger/Logger.hpp
        Starter.cpp
        Server/command/Command.hpp
        Server/command/CommandOrigin.hpp
        Server/command/CommandManager.cpp
        Server/command/CommandManager.h
        Server/utils/Utils.hpp
        Server/command/defaults/StopCommand.cpp
        Server/command/defaults/StopCommand.h
        Server/command/defaults/HelpCommand.cpp
        Server/command/defaults/HelpCommand.h
        Server/command/defaults/VersionCommand.cpp
        Server/command/defaults/VersionCommand.h
        Server/actor/Actor.hpp
        Server/actor/MessageReciever.hpp
        Server/actor/Console.hpp
        Server/actor/player/Player.hpp
        Server/actor/Mob.hpp
        Server/utils/StdEnv.h
        Include/nlohmann/json.hpp
        Server/lang/LangConfiguration.hpp)

include_directories(.)
include_directories(Include)

link_directories(.)

add_executable(BedrockPowder ${BedrockPowder_src})