//
// Created by pepef on 09.08.2022.
//

#ifndef BEDROCKPOWDER_LOGINPACKET_HPP
#define BEDROCKPOWDER_LOGINPACKET_HPP


#include "Server/network/PacketType.hpp"
#include "Server/network/MCPEPacket.hpp"

#include "Server/utils/StdEnv.h"
#include "Server/network/ProtocolInfo.h"
#include "nlohmann/json.hpp"
#include "Server/exception/GenericException.hpp"

#include <vector>

class JwtChain {
public:
    std::vector<std::string> chain;
};

class LoginPacket : public MCPEPacket<ClientSide> {

public:
    LoginPacket() : MCPEPacket<ClientSide>(PacketIDs::login_packet) {}

    LoginPacket(int protocol, JwtChain* chainDataJwt, std::string clientDataJwt) : MCPEPacket<ClientSide>(PacketIDs::login_packet) {
        this->protocol = protocol;
        this->chain = chainDataJwt;
        this->client_data_jwt = std::move(clientDataJwt);
    }

    void read(BinaryStream* binaryStream) override {
        this->protocol = binaryStream->get_int_be();

        auto rem = binaryStream->get_remaining_bytes();

        this->decodeConnectionRequest((unsigned char*)rem);
    }

    void write(BinaryStream* binaryStream) override {
        binaryStream->put_var_int(this->protocol);

    }

    int protocol{};
    JwtChain* chain{};
    std::string client_data_jwt;
protected:
    void decodeConnectionRequest(const unsigned char* binary) {
        auto* reader = new BinaryStream(binary);

        auto chainDataJsonLength = reader->get_int_le();

        if(chainDataJsonLength <= 0) {
            throw GenericException("LoginPacket: Length of chain data JSON must be positive");
        }

        nlohmann::basic_json tho((char*)reader->get_bytes(chainDataJsonLength));

        //todo map json...

        auto clientDataJwtLength = reader->get_int_le();

        if(clientDataJwtLength <= 0) {
            throw GenericException("LoginPacket: Length of clientData JWT must be positive");
        }

        this->client_data_jwt = (char *)reader->get_bytes(clientDataJwtLength);
    }

    [[nodiscard]]
    std::string encodeConnectionRequest() const {
        const unsigned char* uc;
        auto* writer = new BinaryStream(const_cast<const unsigned char*>(uc));
        auto chainDataJson = nlohmann::basic_json(this->chain->chain);

        std::string jsonstr = nlohmann::to_string(chainDataJson);
        writer->put_bytes(((int8_t*) jsonstr.c_str()), strlen(jsonstr.c_str()));

        writer->put_bytes(((int8_t*) this->client_data_jwt.c_str()), strlen(this->client_data_jwt.c_str()));

        return (const char*)writer->buffer;
    }

    //todo: Packethandlerinterface.
};

#endif //BEDROCKPOWDER_LOGINPACKET_HPP
