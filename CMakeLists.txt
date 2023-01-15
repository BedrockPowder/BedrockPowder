cmake_minimum_required(VERSION 3.22)
project(BedrockPowder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

set(BedrockPowder_src Server/BedrockPowder.cpp Server/BedrockPowder.h Server/Constants.h Server/logger/Logger.hpp Starter.cpp Server/command/Command.hpp Server/command/CommandOrigin.hpp Server/command/CommandManager.cpp Server/command/CommandManager.h Server/utils/Utils.hpp Server/command/defaults/StopCommand.cpp Server/command/defaults/StopCommand.h Server/command/defaults/HelpCommand.cpp Server/command/defaults/HelpCommand.h Server/command/defaults/VersionCommand.cpp Server/command/defaults/VersionCommand.h Server/actor/Actor.hpp Server/actor/MessageReciever.hpp Server/actor/Console.hpp Server/actor/player/Player.hpp Server/actor/Mob.hpp Server/utils/StdEnv.h Server/config/LangConfiguration.hpp Server/network/MCPEPacket.hpp Server/utils/BinaryStream.hpp Server/network/ProtocolInfo.h Server/config/ServerConfiguration.hpp Server/command/defaults/ListCommand.cpp Server/command/defaults/ListCommand.h Server/network/raknet/RakNetHandler.hpp Include/stackoverflow/color Server/math/Vector2d.hpp Server/network/PacketType.hpp Server/math/Vector3d.hpp Server/network/PacketBase.hpp Server/exception/GenericException.hpp Server/network/packets/LoginPacket.hpp Server/network/handler/MCPEPacketHandler.hpp Server/network/packets/PlayStatusPacket.hpp Server/network/pstorage/PacketStorage.hpp Server/network/pstorage/PacketFinder.hpp Server/utils/MCTextFormat.h Server/command/defaults/SayCommand.cpp Server/command/defaults/SayCommand.h)

add_subdirectory(RakNet/RakNet)
add_subdirectory(MiniZ)
add_subdirectory(Zlib)

include_directories(.)
include_directories(Include)

include_directories(RakNet/RakNet)
include_directories(MiniZ)
include_directories(Zlib)

link_directories(.)

add_executable(BedrockPowder ${BedrockPowder_src})

target_link_libraries(BedrockPowder raknet)
target_link_libraries(BedrockPowder miniz)
target_link_libraries(BedrockPowder Zlib/Debug/zlibd)
