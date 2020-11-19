#include <allegro.h>
#include "Global.h"
#include "Menu.h"
#include "Personagem.h"
#include "LevelManager.h"
#include "Inimigo.h"

//instanciaçao dos objetos
Menu menu;
Personagem pers;
LevelManager lev_manager;
Inimigo inim;


//funçoes prototipadas
void init();
void deinit();
void fase_1(BITMAP* buffer,BITMAP* heroi, BITMAP* mundo, BITMAP* ground,
            BITMAP* vida, BITMAP* inimigo, int timer);

//variaveis globais
bool fase1_musica_ativado = false;
volatile int timer;
bool ativado = true;

//funçoes globais definidas
void incrementa_timer() { timer++; }
END_OF_FUNCTION(incrementa_timer)

int main(){

    //INITS
    init();
    menu.init();
    pers.init();
    lev_manager.init();
    inim.init();

    //BITMAPS
    BITMAP* buffer = create_bitmap(800,600);
    BITMAP* cursor = load_bitmap("Sprites/cursor.bmp", NULL);
    BITMAP* menu_bmp = load_bitmap("Sprites/menu.bmp", NULL);
    BITMAP* heroi = load_bitmap("Sprites/personagem.bmp", NULL);
    BITMAP* mundo = load_bitmap("Sprites/industrial_background1.bmp", NULL);
    BITMAP* ground = load_bitmap("Sprites/Ground.bmp", NULL);
    BITMAP* vida = load_bitmap("Sprites/vida.bmp", NULL);
    BITMAP* inimigo = load_bitmap("Sprites/inimigo.bmp", NULL);

    //MUSICAS
    //SAMPLE*  musica_menu = load_sample("Sons/techological.wav");
    //play_sample(musica_menu,255,80,1000,TRUE);

    //CONFIGURAÇAO DO TIMER
    timer = 0;
    LOCK_FUNCTION(incrementa_timer)
    LOCK_VARIABLE(timer)
    install_int_ex(incrementa_timer, BPS_TO_TIMER(60));
    srand(time(NULL));
    int marcador = timer;

    while(!key[KEY_ESC]){
        while(timer > 0){
            if(menu.ativado){
                menu.desenhar(buffer,menu_bmp,cursor);
                masked_blit(buffer,screen,0,0,0,0,screen_width,screen_height);
            }
            else{
                //stop_sample(musica_menu);
                fase_1(buffer, heroi, mundo, ground, vida, inimigo, timer);
            }
            timer--;
        }
    }

    deinit();
}
END_OF_MAIN()


void fase_1(BITMAP* buffer, BITMAP* heroi, BITMAP* mundo, BITMAP* ground,
             BITMAP* vida, BITMAP* inimigo, int timer){
    //UPDATE
    pers.update();
    lev_manager.update(pers, vida);
    inim.update(pers, timer);
    //DRAW
    lev_manager.desenhar(buffer, mundo, pers, ground, vida);
    inim.desenhar(buffer, inimigo);
    pers.desenhar(buffer, heroi);
    if(ativado){
        //SAMPLE* musica = load_sample("Sons/22 Subboss Theme.wav");
        //play_sample(musica, 255,80,1000, FALSE);
        ativado = false;
    }


    blit(buffer, screen, 0,0,0,0,screen_width, screen_height);
    clear(buffer);
}

void init() {
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0)
		depth = 32;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, screen_width, screen_height, 0, 0);
	if (res != 0) {
		allegro_message(allegro_error);
		exit(-1);
	}
	install_timer();
	install_keyboard();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_mouse();
	/* add other initializations here */
}

void deinit() {
	clear_keybuf();
	/* add other deinitializations here */
}
