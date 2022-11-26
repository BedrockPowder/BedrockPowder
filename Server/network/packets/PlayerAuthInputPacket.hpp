#ifndef BEDROCKPOWDER_PLAYERAUTHINPUTPACKET_HPP
#define BEDROCKPOWDER_PLAYERAUTHINPUTACKET_HPP


#include "Server/network/PacketType.hpp"
#include "Server/network/MCPEPacket.hpp"

#include "Server/utils/StdEnv.h"
#include "Server/network/ProtocolInfo.h"

struct Vec2
{
   float x,y;
};

struct Vec3
{
   float x,y,z;
};

enum AuthInputAction {
    ASCEND,
    DESCEND,
    NORTH_JUMP,
    JUMP_DOWN,
    SPRINT_DOWN,
    CHANGE_HEIGHT,
    JUMPING,
    AUTO_JUMPING_IN_WATER,
    SNEAKING,
    SNEAK_DOWN,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    WANT_UP,
    WANT_DOWN,
    WANT_DOWN_SLOW,
    WANT_UP_SLOW,
    SPRINTING,
    ASCEND_SCAFFOLDING,
    DESCEND_SCAFFOLDING,
    SNEAK_TOGGLE_DOWN,
    PERSIST_SNEAK,
    START_SPRINTING,
    STOP_SPRINTING,
    START_SNEAKING,
    STOP_SNEAKING,
    START_SWIMMING,
    STOP_SWIMMING,
    START_JUMPING,
    START_GLIDING,
    STOP_GLIDING,
    PERFORM_ITEM_INTERACTION,
    PERFORM_BLOCK_ACTIONS,
    PERFORM_ITEM_STACK_REQUEST
};

enum InputMode {

    UNDEFINED,
    MOUSE,
    TOUCH,
    GAME_PAD,
    MOTION_CONTROLLER,
    COUNT
};

 enum ClientPlayMode {
    NORMAL,
    TEASER,
    SCREEN,
    VIEWER,
    REALITY,
    PLACEMENT,
    LIVING_ROOM,
    EXIT_LEVEL,
    EXIT_LEVEL_LIVING_ROOM
};

enum AuthInteractionModel {
    TOUCH,
    CROSSHAIR,
    CLASSIC
};

enum PlayerActionType {

    START_DESTROY_BLOCK,
    ABORT_DESTROY_BLOCK,
    STOP_DESTROY_BLOCK,
    GET_UPDATED_BLOCK,
    DROP_ITEM,
    START_SLEEPING,
    STOP_SLEEPING,
    RESPAWN,
    START_JUMP,
    START_SPRINTING,
    STOP_SPRINTING,
    START_SNEAKING,
    STOP_SNEAKING,
    CREATIVE_DESTROY_BLOCK,
    CHANGE_DIMENSION_ACK,
    START_GLIDING,
    STOP_GLIDING,
    DENY_DESTROY_BLOCK,
    CRACK_BLOCK,
    CHANGE_SKIN,
    UPDATED_ENCHANTING_SEED,
    START_SWIMMING,
    STOP_SWIMMING,
    START_SPIN_ATTACK,
    STOP_SPIN_ATTACK,
    INTERACT_WITH_BLOCK,
    PREDICT_DESTROY_BLOCK,
    CONTINUE_DESTROY_BLOCK,
    START_ITEM_USE_ON,
    STOP_ITEM_USE_ON
};

struct PlayerBlockActionData 
{
    PlayerActionType action;
    Vec3 position;
    int facing;
};

class PlayerAuthInputPacket : public MCPEPacket<ClientSide> {

public:
   PlayerAuthInputPacket() : MCPEPacket<ClientSide>(PacketIDs::player_auth_input_packet) {}
   float yaw;
   float pitch;
   float headYaw;
   Vec3 position;
   Vec2 motion;
   set<AuthInputAction> inputData;
   InputMode inputMode;
   ClientPlayMode playMode;
   AuthInteractionModel interactionModel;
   Vec3 vrGazeDirection;
   long tick;
   Vec3 delta;
   map<PlayerActionType, PlayerBlockActionData> blockActionData;
   PlayerAuthInputPacket(float _yaw,float _pitch,float head,Vec3 pos,Vec2 mot,set<AuthInputAction> input,InputMode inputmode,ClientPlayMode play,AuthInteractionModel interaction,Vec3 vrGazeDir,long _tick,Vec3 _delta,map<PlayerActionType, PlayerBlockActionData> blockAction)
   {
     yaw = _yaw;
     pitch = _pitch;
     headYaw = head;
     position = pos;
     motion = mot;
     inputData = input;
     inputMode = inputmode;
     playMode = play;
     interactionModel = interaction;
     vrGazeDirection = vrGazeDir;
     tick = _tick;
     delta = _delta;
     blockActionData = blockAction;
   }
   void read(BinaryStream* stream) override
   {
      yaw = stream->get_float_le();
      pitch = stream->get_float_le();
      position = Vec3(stream->get_float_le(),stream->get_float_le(),stream->get_float_le());
      motion = Vec2(stream->get_float_le(),stream->get_float_le());
      headYaw = stream->get_float_le();
      long inputdata = stream->unsigned_long_le();
      for (int i = 0; i < 37; ++i)
      {
         if ((inputdata) & (1 << i))
            inputData.insert(inputdata);
      }
      inputMode = stream->get_unsigned_int_le();
      playMode = stream->get_unsigned_int_le();
      interactionModel = stream->get_unsigned_int_le();
      if (playMode == 4)
         vrGazeDirection = Vec3(0,0,0);
      tick = stream->unsigned_long_le();
      delta = Vec3(stream->get_float_le(),stream->get_float_le(),stream->get_float_le());
   }
};
