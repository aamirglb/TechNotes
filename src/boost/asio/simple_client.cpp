#include <iostream>
#include "olc_net.h"

enum class CustomMsgTypes : uint32_t
{
    FireBullet,
    MovePlayer,
};

int main() {
    olc::net::message<CustomMsgTypes> msg;
    msg.header.id = CustomMsgTypes::FireBullet;
    
    int a = 1;
    bool b = true;
    float c = 3.14159f;

    struct {
        float x = 2.22f;
        float y = 4.44f;
    } d[5];

    msg << a << b << c << d;
    a = 99;
    b = false;
    c = 0.0f;

    msg >> d >> c >> b >> a;

    std::cout << "a: " << a << " b: " << b << 
        " c: " << c << " d: " << d[0].x << '\n';
    return 0;
}