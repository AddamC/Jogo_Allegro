#pragma once
#include <allegro.h>
#include "Shooting.h"
#include "global.h"

class Personagem
{
public:
    float x, y, pulo_max, vel_x = 2.2, vel_y, accel = 0.08, gravity = 0.5;
    int i, j, chao;
    int contVidas = 3;

    bool ativo = true, direita = false;
    bool naEscada = false;
    bool grounded = true, altura_max = false, idle, crouch;
    bool pressionado = false;
    bool morto = false;

    //instanciaçao de objetos
    Shooting projetil;

    Personagem(); //construtor padrao

    void init();
    void update();
    void desenhar(BITMAP*buffer, BITMAP*heroi);
    void cair();
    void controls();
};

Personagem::Personagem()
{

}


void Personagem::init()
{
    x = 50;
    chao = 900;
    pulo_max = chao;
    y = 450;
    grounded = false;
    contVidas = 3;
    morto = false;
    naEscada = false;
    direita = false;

    projetil.x = x+30;
    projetil.y = y-15;
}

void Personagem::update()
{

    vel_x = vel_x + accel;
    if(x > screen_width)     //LIMITES DA FASE
    {
        x = screen_width;
    }

    ///MORTE----------------------------//
    if(y > 890)     //LIMITES DA FASE
    {
        morto = true;
    }
    if(contVidas == 0)
    {
        ativo = false;
    }
    if(morto)
    {
        contVidas--;
        x = 0;
        y = 450;
        vel_y = 0.5;
        morto = false;
    }
    ///---------------------------------**
    //POSIÇOES
    if(x < 0)
    {
        x = 0;
    }
    if(y < 90)
        y = 90;

    //tiro - update
    Personagem::controls();

    projetil.vel_x += projetil.accel;
    projetil.vel_x = 4;

    if(direita)
        projetil.x -= projetil.vel_x;
    if(!direita)
        projetil.x += projetil.vel_x;

    if(projetil.x > 800 || projetil.x < 0)
    {
        projetil.ativo = false;
    }

}

void Personagem::controls()
{
    ///TIRO-------------------------------//

    if(key[KEY_DOWN] && !projetil.ativo && !morto)
    {
        projetil.x = x + 50;
        projetil.y = y - 15;
        projetil.ativo = true;
    }
    /*
    if(key[KEY_UP]){
        projetil.init();
        ativo = true;
        init();
    }
    */
    ///VERIFICAÇAO DO ATIVO PARA ACESSAR AS UTILIDADES DO PERSONAGEM
    if(ativo)
    {
        if(key[KEY_RIGHT])
        {
            x = x + vel_x;
        }
        if(key[KEY_LEFT])
        {
            x = x - vel_x;
        }
        if(!key[KEY_LEFT] && !key[KEY_RIGHT])  //QUANDO NAO ESTA ANDANDO
        {
            vel_x = 2.2;
        }
        if(grounded)
        {
            if(key[KEY_S])
            {
                crouch = true;
            }
            else crouch = false;
        }/*
        if(naEscada){
            if(key[KEY_UP]){
                y--;
            //grounded = false;
        }
    }
    */

        ///MECANICA DO PULO---------------------------------------------//
        if(!crouch)
        {
            if(key[KEY_UP] && grounded )
            {
                grounded = false;
                vel_y = 13;
            }

            if(grounded && !naEscada)
            {
                y = chao;
                altura_max = false;
            }

            //Subida do pulo ate altura max definida
            if(!grounded && !altura_max)
            {
                vel_y = vel_y - gravity;
                y = y - vel_y;
                if(vel_y == 0)
                {
                    altura_max = true;
                }
            }

            //Descida do pulo
            if(altura_max && !grounded)
            {
                grounded = false;
                vel_y = vel_y + gravity;
                y = y + vel_y;
            }
            if(y >= chao)
            {
                grounded = true;
                altura_max = false;
                vel_y = 1.2;
            }
        }
    }
}

void Personagem::desenhar(BITMAP*buffer, BITMAP*heroi)
{

    ///TESTE DOS VALORES-------------------------------------------//
    textprintf_ex(buffer, font, 10, 10, makecol(255, 100, 0),
                  -1, "posicao personagem y: %i", y);
    textprintf_ex(buffer, font, 10, 20, makecol(255, 100, 0),
                  -1, "naEscada: %i", naEscada);
    textprintf_ex(buffer, font, 10, 30, makecol(255, 100, 0),
                  -1, "posicao crouch: %i", crouch);
    textprintf_ex(buffer, font, 10, 40, makecol(255, 100, 0),
                  -1, "vel_y: %f", vel_y);
    textprintf_ex(buffer, font, 10, 50, makecol(255, 100, 0),
                  -1, "posicao personagem x: %i", x);
    textprintf_ex(buffer, font, 10, 60, makecol(255, 100, 0),
                  -1, "grounded: %i", grounded);
    textprintf_ex(buffer, font, 10, 70, makecol(255, 100, 0),
                  -1, "direita: %i", direita);

    ///FIM DOS TESTES----------------------------------------------//


    //desenhar personagem
    if(ativo)
    {
        rectfill(buffer, x,y-20,x+30,y, makecol(255,255,0));
    }

    if(crouch && grounded)
    {
        //masked_blit(heroi, buffer, 3,800,x,y, 60,37);
    }
    else
    {
        if(!crouch && grounded)
        {
            //rectfill(buffer, x,y-20,x+30,y, makecol(255,255,0));
            //masked_blit(heroi, buffer, 0,0,x,y, 800,600);
        }
        if(!grounded && !crouch)
        {
            //rectfill(buffer, x,y-20,x+30,y, makecol(255,255,0));
            //masked_blit(heroi, buffer, 0,0,x,y, 800,600);
        }
    }

    ///TIRO--------------------------------------------------------------------------///
    if(projetil.ativo)
    {
        rectfill(buffer, projetil.x, projetil.y, projetil.x+10, projetil.y+10, makecol(0,0,255));
    }
}
