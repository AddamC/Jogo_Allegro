#include <allegro.h>

class Escada{
public:
    float x1,y1, x2,y2; //DEFINIÇAO DA DIMENSAO DO GROUND
    Escada();
    Escada(float, float, float, float);
    void setEscada(float, float, float, float);
};

Escada::Escada(){
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
}
Escada::Escada(float x1, float x2, float y1, float y2){
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;

}

void Escada::setEscada(float x1, float x2, float y1, float y2){
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}


