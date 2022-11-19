#include <iostream>
#include "olc_net.h"

enum class CustomMsgTypes : uint32_t
{
    FireBullet,
    MovePlayer
};

int main(){
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::FireBullet;
}