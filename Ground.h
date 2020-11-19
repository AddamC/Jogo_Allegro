#include <allegro.h>
#include <deque>

class Ground{
public:
    float x1,y1, x2,y2; //DEFINIÇAO DA DIMENSAO DO GROUND
    Ground();
    Ground(float, float, float, float);
    void setGround(float, float, float, float);
};

Ground::Ground(){
    x1 = 0;
    x2 = 0;
    y1 = 0;
    y2 = 0;
}
Ground::Ground(float x1, float x2, float y1, float y2){
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;

}

void Ground::setGround(float x1, float x2, float y1, float y2){
    this->x1 = x1;
    this->x2 = x2;
    this->y1 = y1;
    this->y2 = y2;
}

