#include <allegro.h>
#include <cstdint>

#include "Global.h"
#include "Menu.h"
#include "Personagem.h"
#include "LevelManager.h"
#include "Inimigo.h"


//instancia�ao dos objetos
Menu menu;
Personagem pers;
LevelManager lev_manager;
Inimigo inim;


void init();
void deinit();
void fase_1(BITMAP* buffer, BITMAP* heroi, BITMAP* mundo, BITMAP* ground,
            BITMAP* vida, BITMAP* inimigo, int timer);

volatile int timer;

// TODO: make this work
uint8_t fps_options[] = {30, 60, 120};
uint8_t current_fps_index = 1; // Default to 60 FPS

uint8_t current_fps_target = 60;

bool ativado = true;
bool use_vsync = true;

void increment_timer() { timer++; }
END_OF_FUNCTION(increment_timer)

int main(){
    srand(time(NULL));

    init();
    menu.init();
    pers.init();
    lev_manager.init();
    inim.init();

    BITMAP* buffer = create_bitmap(screen_width, screen_height);
    BITMAP* cursor = load_bitmap("Sprites/cursor.bmp", NULL);
    BITMAP* menu_bmp = load_bitmap("Sprites/menu.bmp", NULL);
    BITMAP* heroi = load_bitmap("Sprites/personagem.bmp", NULL);
    BITMAP* mundo = load_bitmap("Sprites/industrial_background1.bmp", NULL);
    BITMAP* ground = load_bitmap("Sprites/Ground.bmp", NULL);
    BITMAP* vida = load_bitmap("Sprites/vida.bmp", NULL);
    BITMAP* inimigo = load_bitmap("Sprites/inimigo.bmp", NULL);

    //SAMPLE*  musica_menu = load_sample("Sons/techological.wav");
    //play_sample(musica_menu,255,80,1000,TRUE);

    timer = 0;
    LOCK_FUNCTION(increment_timer)
    LOCK_VARIABLE(timer)
    install_int_ex(increment_timer, BPS_TO_TIMER(current_fps_target));

    while(!key[KEY_ESC]){
        // Handle VSync and FPS toggling
        if (key[KEY_V]) {
            use_vsync = !use_vsync;
            // Re-initialize graphics mode to apply VSync change
            set_gfx_mode(GFX_AUTODETECT_WINDOWED, SCREEN_W, SCREEN_H, 0, 0);
            if (use_vsync) {
                vsync();
            }
        }
        if (key[KEY_1]) {
            current_fps_target = 30;
            install_int_ex(increment_timer, BPS_TO_TIMER(current_fps_target));
        }
        if (key[KEY_2]) {
            current_fps_target = 60;
            install_int_ex(increment_timer, BPS_TO_TIMER(current_fps_target));
        }
        if (key[KEY_3]) {
            current_fps_target = 120;
            install_int_ex(increment_timer, BPS_TO_TIMER(current_fps_target));
        }

        while(timer > 0){
            if(menu.ativado) {
                menu.update();
                menu.draw(buffer, menu_bmp, cursor);
                masked_blit(buffer,screen, 0, 0, 0, 0, screen_width, screen_height);
            } else {
                //stop_sample(musica_menu);
                fase_1(buffer, heroi, mundo, ground, vida, inimigo, timer);
            }
            timer--;
        }
    }

    // De-initialize Allegro and free resources
    destroy_bitmap(buffer);
    destroy_bitmap(cursor);
    destroy_bitmap(menu_bmp);
    destroy_bitmap(heroi);
    destroy_bitmap(mundo);
    destroy_bitmap(ground);
    destroy_bitmap(vida);
    destroy_bitmap(inimigo);
    //destroy_sample(musica_menu);
    //destroy_sample(musica_fase1);
    deinit();

    return 0;
}
END_OF_MAIN()


void fase_1(BITMAP* buffer, BITMAP* heroi, BITMAP* mundo, BITMAP* ground,
             BITMAP* vida, BITMAP* inimigo, int timer){
    //UPDATE
    pers.update();
    lev_manager.update(pers, vida);
    inim.update(pers, timer);
    //DRAW
    lev_manager.draw(buffer, mundo, pers, ground, vida);
    inim.draw(buffer, inimigo);
    pers.draw(buffer, heroi);
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
		allegro_message("%s", allegro_error);
		exit(-1);
	}

    if (use_vsync) {
        vsync();
    }

	install_timer();
	install_keyboard();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	install_mouse();
}

void deinit() {
	clear_keybuf();
}