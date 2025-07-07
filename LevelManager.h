#include <allegro.h>
#include "Personagem.h"
#include "Ground.h"
//#include "inimigo.h"
#include <vector>
#include <iostream>
#include <time.h>
#include "Global.h"
//#include "PickUps.h"
#include "Escada.h"

using namespace std;

class LevelManager
{
public:

    int altura_mapa;

    void init();
    void update(Personagem &pers, BITMAP* &vida); ///RETORNANDO POR REFERENCIA PARA ALTERAR VALORES DOS ATRIBUTOS DO PERSONAGEM EM TEMPO REAL
    void draw(BITMAP*buffer, BITMAP* mundo, Personagem &pers, BITMAP* ground, BITMAP* vida);
    bool collided(Personagem &pers, Ground plataformas);
    Ground g1 {0,100,500,600};
    Ground g2 {150,220,300,350};
    Ground g3 {300,370,220,250};
    Ground g4 {225,260,500,530};
    Ground g5 {120,150,400,430};
    Ground g6 {400,800,400,550};
    Ground g7 {470,505,250,280};
    Ground g8 {100,600,100,130};
    Escada e1 {50,100,200,500};
//    PickUps p1{230,250,450,470};
    Ground plataformas[10];
    void criarGround();

};

bool LevelManager::collided(Personagem &pers,Ground plataformas)
{
    if(pers.x+30 > plataformas.x1 && pers.x+10 < plataformas.x2 &&
            pers.y+40 < plataformas.y1+50 && pers.y > plataformas.y1-10)
    {

        pers.grounded = true;
        pers.chao = plataformas.y1;

        return true;
    }

    return false;
}


void LevelManager::init()
{
    //pers.pos_mundo = mundo_altura_max-150; //POSI�AO DO PERSONAGEM NA SPRITE CONSIDERADO SIMILAR AO DA SCREEN
    altura_mapa = 0;
    for(int i = 0,x = rand()%650+x, y = rand()%500; i < 10; i++,x = rand()%650, y = rand()%500)
    {
        Ground *g = new Ground(x, rand()%800+x, y, rand()%600+y);
        plataformas[i] = *g;
        //plataformas.push_back(g);
    }
}
void LevelManager::update(Personagem &pers, BITMAP* &vida)
{
    ///COLISOES----------------------------------------------///
    // for(int i=0; i<10; i++)
    // {
    //     collided(pers, plataformas[i]);
    // }

    if(!collided(pers, g1))
    {
        //pers.vel_y = 0;
        pers.chao = 900;
        if(pers.y != pers.chao)
            pers.grounded = false;
    }

    // collided(pers, g2);
    // collided(pers, g3);
    // collided(pers, g5);
    // collided(pers, g4);
    // collided(pers, g6);
    // collided(pers, g7);
    // collided(pers, g8);

    //escada
    if(pers.x+30 > e1.x1)
    {
        pers.naEscada = true;
    }

    //COLISAO DA ESTRELA
    /*
        if(pers.x < p1.x2 && pers.x+30 > p1.x1 && pers.y > p1.x1 && pers.y < p1.y2){
            vida = load_bitmap("Sprites/personagem.bmp", NULL);
        }
    */
}
void LevelManager::draw(BITMAP*buffer, BITMAP* mundo,Personagem &pers, BITMAP* ground, BITMAP* vida)
{

    for(int i = 0; i < 10; i++)
    {
        rect(buffer, plataformas[i].x1, plataformas[i].y1, plataformas[i].x2, plataformas[i].y2, makecol(255,0,0));
        textprintf_ex(buffer, font, plataformas[i].x1-10, plataformas[i].y1, makecol(255, 100, 0),
                      -1, "%i", i);
    }
    blit(mundo, buffer, 0, 0,0,0,800,600);
    rectfill(buffer, g1.x1, g1.y1, g1.x2, g1.y2, makecol(255,0,0));
    rectfill(buffer, g6.x1, g6.y1, g6.x2, g6.y2, makecol(255,200,100));
    rectfill(buffer, g7.x1, g7.y1, g7.x2, g7.y2, makecol(255,200,100));
    rectfill(buffer, g8.x1, g8.y1, g8.x2, g8.y2, makecol(10,70,100));
    rectfill(buffer, e1.x1, e1.y1, e1.x2, e1.y2, makecol(255,70,100));
    masked_blit(ground, buffer, 0,0,g2.x1, g2.y1,screen_width,screen_height);
    masked_blit(ground, buffer, 0,0,g3.x1, g3.y1,screen_width,screen_height);
    masked_blit(ground, buffer, 0,0,g4.x1, g4.y1,35,screen_height);
    masked_blit(ground, buffer, 0,0,g5.x1, g5.y1,35,screen_height);
//    masked_blit(vida, buffer, 0,0,p1.x1, p1.y1,screen_width, screen_height);
//    rectfill(buffer, p1.x1, p1.y1, p1.x2, p1.y2,makecol(255,255,0));
}

