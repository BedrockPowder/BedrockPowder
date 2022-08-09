//
// Created by pepef on 26.07.2022.
//

#ifndef BEDROCKPOWDER_PACKETTYPE_HPP
#define BEDROCKPOWDER_PACKETTYPE_HPP
class SideBase {
public:
    virtual bool isClientSide() = 0;
    virtual bool isServerSide() = 0;
};
class ClientSide : public SideBase {
public:
    bool isClientSide() override {
       return true;
    }
    bool isServerSide() override {
        return false;
    }
};
class ServerSide : SideBase {
public:
    bool isClientSide() override {
        return false;
    }
    bool isServerSide() override {
        return true;
    }
};
class AllSide : public SideBase {
public:
    bool isClientSide() override {
        return true;
    }
    bool isServerSide() override {
        return true;
    }
};

#endif //BEDROCKPOWDER_PACKETTYPE_HPP
