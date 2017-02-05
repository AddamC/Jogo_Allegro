#pragma once
#include <allegro.h>


class Shooting{
public:
    float vel_x = 2.2, accel = 0.08;
    float x;
    float y;
    bool ativo = false;
    Shooting();
    void init();
    void update();
};

Shooting::Shooting(){
    x = 0;
    y = 0;
    ativo = false;
    vel_x = 4;
    accel = 0.2;
}

void Shooting::init(){
    x = 0;
    y = 0;
    ativo = false;

}

void Shooting::update(){
}
