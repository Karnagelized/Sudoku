#ifndef MENU_H
#define MENU_H

#include "graphics.h"

enum button_values {
   NONE = -1,
   DIFFICULT,
   ABOUT,
   EXIT,
   N_MENU_BUTTONS,
   DIFFICULT_E,
   DIFFICULT_N,
   DIFFICULT_H,
   N_DIFFICULT_BUTTONS,
   GAME,
   GAME_DIFFICULT,
   GAME_EXIT,
   N_GAME_BUTTONS,
   WIN,
   RESTART
};

struct Button {
   int left;
   int top;
   int width;
   int height;
   IMAGE *image;
};

// Procedures and Functions
void load();
void start();
void menu();
void create_button(int, int, int, const char*);
void create_game_button(int, int, int, const char*);
void put_menu_img();
void put_difficult_img();
void put_game_img();
int select_button();
int select_difficult_button();
int select_game_button();
void about();
void backlight_select_cell(bool);
void win();
void lose();
void close();

#endif