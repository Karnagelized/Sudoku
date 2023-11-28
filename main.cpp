#include "menu.h"
#include "graphics.h"
#define WIDTH  800
#define HEIGHT 600

int main() {
   initwindow(WIDTH, HEIGHT, "Sudoku");
   // Load Pictire's
   load();
   // Start Game
   start();
   // Init and create Menu on screen
   menu();
   
   closegraph();
   return 0;
}