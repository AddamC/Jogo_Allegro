#pragma once
#include <allegro.h>
#include "Personagem.h"

class Inimigo{
public:
    float x1,x2,y1,y2,chao;
    bool ativo = true;
    bool seguindo = true;
    bool direita, grounded, hit;
    int marcador;
    int contVidas = 2;
    Inimigo();
    void init();
    void desenhar(BITMAP*buffer,BITMAP*vilao);
    void update(Personagem &pers, int timer);
    void movimento(Personagem &pers);
};

Inimigo::Inimigo(){

}

void Inimigo::init(){
    ativo = true;
    seguindo = true;
    direita = true;
    grounded = true;
    hit = false;
    chao = 500;
    x1 = 900;
    x2 = 900 + 159;
    y1 = 400 - 171; //tamanho da imagem
    y2 = 400;
    contVidas = 2;
    marcador = 3;
}

void Inimigo::movimento(Personagem &pers){
    if(seguindo){
        if(direita)
            x1++;
        if(!direita)
            x1--;
        if(y2 > pers.y){
            y2--;
            y1--;
        }
        if(y2 < pers.y){
            y2++;
            y1++;
        }
    }
}

void Inimigo::update(Personagem &pers, int timer){
    if(ativo){
        movimento(pers);
        if(pers.x < x1){
            direita = false;
            pers.direita = false;
        }
        if(pers.x > x2){
            direita = true;
            pers.direita = true;
        }
        y1 = y2 - 100;
        x2 = x1 + 100;



        //colisao
        if(pers.x+30 > x1 && pers.x < x2 && pers.y > y1 && pers.y-20 < y2){
            pers.morto = true;
        }
        //Tomar dano
        if(pers.projetil.x+5 > x1 && pers.projetil.x < x2 && pers.projetil.y >y1 &&
           pers.projetil.y+10 < y2 && pers.projetil.ativo){
            hit = true;
        }
        if(hit){
            contVidas--;
            pers.projetil.ativo = false;
            hit = false;
        }
        if(contVidas < 0){
            ativo = false;
        }
    }
    /*
    if(pers.x+30 > x1 && pers.x < x2 && pers.y+5 > y1){
        contVidas--;
        pers.y-=10;
    }
    */
}

void Inimigo::desenhar(BITMAP*buffer, BITMAP*vilao){

    textprintf_ex(buffer, font, x1, y1-30, makecol(255, 0, 255),
                    -1, "Vida inimigo: %i", contVidas);
    if(contVidas < 0){
        textout_ex(buffer,font, "VOCE VENCEU", screen_width/2 - 100, screen_height/2, makecol(255,255,0),-1);
    }

    /*
    if(!direita)
        masked_blit(vilao, buffer,0,0,x1,y1,800,600);
    if(direita)
        draw_sprite_ex(buffer, vilao, x1,y1,DRAW_SPRITE_NORMAL,DRAW_SPRITE_H_FLIP);
   */
    if(ativo){
        rectfill(buffer, x1,y1,x2,y2, makecol(200,10,50));
    }
    if(!ativo)
        rectfill(buffer, x1,y1,x2,y2, makecol(0,0,0));
}

