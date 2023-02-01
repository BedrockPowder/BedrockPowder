cmake_minimum_required(VERSION 3.22)
project(BedrockPowder)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BUILD_TYPE Release)

file(GLOB BedrockPowder_src
  Starter.cpp
  Server/*.cpp
  Server/*.h
  Server/logger/*.hpp
  Server/command/*.hpp
  Server/command/*.cpp
  Server/command/*.h
  Server/command/defaults/*.cpp
  Server/command/defaults/*.h
  Server/utils/*.hpp
  Server/utils/*.h
  Server/actor/*.hpp
  Server/actor/player/*.hpp
  Server/config/*.hpp
  Server/math/*.hpp
  Server/exception/*.hpp
  Server/network/*.hpp
  Server/network/*.h
  Server/network/raknet/*.hpp
  Server/network/packets/*.hpp
  Server/network/handler/*.hpp
  Server/network/pstorage/*.hpp
  Include/stackoverflow/color
)

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
