#pragma once
#include <allegro.h>


class Menu{
public:
    bool ativado, pausa_ativado;
    Menu();
    void init();
    void desenhar(BITMAP*buffer, BITMAP* menu, BITMAP* cursor);
    void pausa(BITMAP* buffer, BITMAP* pausa);
};

Menu::Menu(){}

void Menu::init(){
    ativado = true;
    pausa_ativado = false;
}

void Menu::desenhar(BITMAP*buffer, BITMAP*menu, BITMAP* cursor){  //MENU INICIAL
        masked_blit(menu, buffer, 0,0,0,0,800,600);
        masked_blit(cursor,buffer,0,0,mouse_x, mouse_y,800,600);
        if(key[KEY_ENTER])
        {
            clear(menu);
            ativado = false;
        }
}

void Menu::pausa(BITMAP*buffer,BITMAP*pausa){
    if(key[KEY_P]){
        blit(pausa, buffer,0,0,300,250,800,600);
    }

}
