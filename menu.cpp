#include <iostream>
#include "menu.h"
#include "game.h"
#include "graphics.h"
#include "windows.h"

using namespace std;

Button buttons[N_DIFFICULT_BUTTONS  + 1];
IMAGE *background_image, *rules_image, *start_image;
IMAGE *win_image, *lose_image;
int X_SELECTED = -1, Y_SELECTED = -1;

// Loading buttons
void load() {
   background_image  = loadBMP("images/Background.bmp");
   rules_image = loadBMP("images/Rules_window.bmp");
   start_image = loadBMP("images/Screensaver.bmp");
   win_image = loadBMP("images/win_window.bmp");
   lose_image = loadBMP("images/lose_window.bmp");
   
   create_button(DIFFICULT,  272, 80, "buttons/Start_button.bmp");
   create_button(ABOUT, 272, 245, "buttons/Rules_button.bmp");
   create_button(EXIT,  272, 410, "buttons/Exit_button.bmp");
   create_button(DIFFICULT_E, 
               272, 80, "buttons/Easy_difficult.bmp");
   create_button(DIFFICULT_N,
               272, 245, "buttons/Normal_difficult.bmp");
   create_button(DIFFICULT_H, 
               272, 410, "buttons/Hard_difficult.bmp");
   create_button(GAME_DIFFICULT, 
               30, 470, "buttons/Start_button.bmp");
   create_button(GAME_EXIT, 
               514, 470, "buttons/Exit_button.bmp");
}

// Loading Screensaver
void start() {
   putimage(0, 0, start_image, COPY_PUT);
   Sleep(3000);
   clearviewport();
}

// Main Function
void menu() {
   int state, game_type = -1;
   int key_victory = 2;
   
   while (true) {
      putimage(0, 0, background_image, COPY_PUT);

      // Put buttons considering menu type
      if (game_type == -3) {                // Win
         win();
         game_type = -1;
      } else if (game_type == -2) {     // Lose 
         lose();
         game_type = -1;
      }
      
      if (game_type == -1) {                // Start 
         put_menu_img();
      } else if (game_type == 0) {      // Choose DIFFICULT
         put_difficult_img();   
      } else if (game_type == 1) {      // Game Window
         drow_grid();
         put_game_img();
      }
      
      // Await new state
      state = NONE;
      while (state == NONE) {
         
         if (key_victory != 2) {
            break;
         }
         
         while (mousebuttons() != 1) {
            if (game_type == -1) {
               state = select_button();
            } else if (game_type == 0) {
               state = select_difficult_button();
            } else if (game_type == 1) {
               state = select_game_button();
               backlight_select_cell(false);

               // Check push key 1 - 9
               if (kbhit()) {
                  int key_pressed = getch();
                  
                  if (key_pressed >= 49 && key_pressed <= 57) {
                     if (check_select_cell(Y_SELECTED, X_SELECTED))
                        {
                           push_num_Puzzle(key_pressed,
                                          Y_SELECTED,
                                          X_SELECTED);
                           // Check victory
                           key_victory = check_victory();
                     }
                  }
               }
               
               if (key_victory != 2) {
                  state = RESTART;
                  if (key_victory == 1) {
                     state = WIN;
                  }
                  
                  break;
               }
            }
         }
      }
      
      // Select need state
      switch (state) {
         case DIFFICULT:
            game_type = 0;
            break;
         case GAME_DIFFICULT:
            game_type = 0;
            break;
         case DIFFICULT_E:
            game(DIFFICULT_E);
            game_type = 1;
            break;
         case DIFFICULT_N:
            game(DIFFICULT_N);
            game_type = 1;
            break;
         case DIFFICULT_H:
            game(DIFFICULT_H);
            game_type = 1;
            break;
         case RESTART:
            game_type = -2;
            key_victory = 2;
            break;
         case WIN:
            game_type = -3;
            key_victory = 2;
            break;
         case ABOUT: about(); break;
         case GAME_EXIT: close(); return;
         case EXIT:  close(); return;
      }
   }
}

// Create About Window
void about() {
   putimage(0, 0, rules_image, COPY_PUT);
   getch();
}

// Create About Window
void win() {
   putimage(0, 0, win_image, COPY_PUT);
   getch();
   clearviewport();
}

// Create About Window
void lose() {
   putimage(0, 0, lose_image, COPY_PUT);
   getch();
   clearviewport();
}

// Exit Program
void close() {
   freeimage(background_image);
   freeimage(rules_image);
   freeimage(start_image);
   
   for (int i = 0; i < N_MENU_BUTTONS; i++) {
      freeimage(buttons[i].image);
   }
   
   for (int i = N_MENU_BUTTONS + 1; i < N_DIFFICULT_BUTTONS; i++) {
      freeimage(buttons[i].image);
   }
}

// Create Buttons
void create_button(int i, int left, int top,
                              const char *file_name) {
   buttons[i].image = loadBMP(file_name);
   buttons[i].left     = left;
   buttons[i].top     = top;
   buttons[i].width  = imagewidth(buttons[i].image);
   buttons[i].height = imageheight(buttons[i].image);
}

// Put IMG on Menu - Screen
void put_menu_img() {
   for (int i = 0; i < N_MENU_BUTTONS; i++) {
         putimage(buttons[i].left, buttons[i].top,
                        buttons[i].image, COPY_PUT);
   }
}

// Put IMG on Difficult - Screen
void put_difficult_img() {
   for (int i = N_MENU_BUTTONS + 1; i < N_DIFFICULT_BUTTONS; i++) {
         putimage(buttons[i].left, buttons[i].top,
                        buttons[i].image, COPY_PUT);
   }
}

// Put IMG on Game - Screen
void put_game_img() {
   for (int i = GAME + 1; i < N_GAME_BUTTONS; i++) {
         putimage(buttons[i].left, buttons[i].top,
                        buttons[i].image, COPY_PUT);
   }
}

// Select Buttons on Menu
int select_button() {
   int x, y;
   
   x = mousex();
   y = mousey();
   
   for (int i = 0; i < N_MENU_BUTTONS; i++) {
      if (x > buttons[i].left &&
          x < buttons[i].left + buttons[i].width &&
          y > buttons[i].top &&
          y < buttons[i].top + buttons[i].height)
      {
         return i;
      }
   }
   
   return NONE;
}

// Select Buttons on choose DIFFICULT
int select_difficult_button() {
   int x, y;
   
   x = mousex();
   y = mousey();
   
   for (int i = N_MENU_BUTTONS + 1; i < N_DIFFICULT_BUTTONS; i++) {
      if (x > buttons[i].left &&
          x < buttons[i].left + buttons[i].width &&
          y > buttons[i].top &&
          y < buttons[i].top + buttons[i].height)
      {
         return i;
      }
   }
   
   return NONE;
}

// Backlight selected cell
void backlight_select_cell(bool flag) {
   int x, y;
   
   x = mousex();
   y = mousey();
   
   if (mousebuttons() == 1 &&
        x >= X_BEGIN + 2 &&
        x <= X_BEGIN + SIZE_CELL * P_SIZE - 2 &&
        y >= Y_BEGIN + 2 &&
        y <= Y_BEGIN + SIZE_CELL * P_SIZE - 2)
   {
      drow_grid();
      X_SELECTED = (x - X_BEGIN) / SIZE_CELL;
      Y_SELECTED = (y - Y_BEGIN) / SIZE_CELL;
      
      // Select cell
      cell_paint(X_SELECTED, Y_SELECTED);
   }
   
   // Select cell with flag
   if (flag) {
      cell_paint(X_SELECTED, Y_SELECTED);
   }
}

// Select Buttons on Game
int select_game_button() {
   int x, y;
   
   x = mousex();
   y = mousey();   
   
   for (int i = GAME + 1; i < N_GAME_BUTTONS; i++) {
      if (x > buttons[i].left &&
          x < buttons[i].left + buttons[i].width &&
          y > buttons[i].top &&
          y < buttons[i].top + buttons[i].height)
      {
         return i;
      }
   }
   
   return NONE;
}