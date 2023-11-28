#include <iostream>
#include <ctime>
#include "graphics.h"
#include "menu.h"
#include "game.h"

int Puzzle_Unresolved[P_SIZE][P_SIZE] = {0};
int New_Puzzle[P_SIZE][P_SIZE] = {0};
int count_empty_cell = 0;

using namespace std;

// Print Sudoku
void print_Puzzle(int(*Puzzle)[9]) {
   for (int c = 0; c < P_SIZE; c++) {
      for (int r = 0; r < P_SIZE; r++) {
         cout << Puzzle[c][r] << " ";
      }
      cout << endl;
   }
   cout << endl;
}

// Generate Correct Grid Sudoku
void generate_grid() {
   for (int c = 0; c < P_SIZE; c++) {
      for (int r = 0; r < P_SIZE; r++) {
         New_Puzzle[c][r] = (c * (P_SIZE/3) +
                              c/(P_SIZE/3) + r) %
                              P_SIZE + 1;
      }
   }
}

// Transpose Grid Puzzle
void Transpose_Puzzle() {
   int t;
   
   for(int c = 0; c < P_SIZE; ++c) {
      for(int r = c; r < P_SIZE; ++r) {
         t = New_Puzzle[c][r];
         New_Puzzle[c][r] = New_Puzzle[r][c];
         New_Puzzle[r][c] = t;
      }
   }
}

// Shuffle collum
void shuffle_row(int count_shuffle) {
   for (int i = 0; i < count_shuffle; i++) {
      int temp = 0;
      int area = rand() % (AREA_MAX - AREA_MIN) + AREA_MIN;
      int temp_line1 = rand() % (LINE_MAX - LINE_MIN) + LINE_MIN;
      int temp_line2 = rand() % (LINE_MAX - LINE_MIN) + LINE_MIN;
      int first_line = area * (P_SIZE/3) + temp_line1;
      
      // Check equality line's
      while(temp_line1 == temp_line2) {
         temp_line2 = rand() % (LINE_MAX - LINE_MIN) + LINE_MIN;
      }
      int second_line = area * (P_SIZE/3) + temp_line2;

      if (first_line != second_line) {
         for (int n = 0; n < P_SIZE; n++) {
            int temp = New_Puzzle[first_line][n];
            New_Puzzle[first_line][n] = New_Puzzle[second_line][n];
            New_Puzzle[second_line][n] = temp;
         }
      }
   }
}

// Shuffle row
void shuffle_coll(int count_shuffle) {
   for (int i = 0; i < count_shuffle; i++) {
      Transpose_Puzzle();
      shuffle_row(1);
      Transpose_Puzzle();
   }
}

// Dublicate Grid Puzzle
void Dublicate_grid() {
   int Dublicate_Puzzle[P_SIZE][P_SIZE];
   
   for (int c = 0; c < P_SIZE; c++) {
      for (int r = 0; r < P_SIZE; r++) {
         Puzzle_Unresolved[c][r] = New_Puzzle[c][r];
      }
   }
}

// Remove random selected cell's with considering DIFFICULT
void delete_cells(int DIFFICULT) {
   int need_delete = 40;       // EASY DIFFICULT
   
   if (DIFFICULT == 5) {
      need_delete = 50;         //NORMAL DIFFICULT
   } else if (DIFFICULT == 6) {
      need_delete = 60;         // HARD DIFFICULT
   }

   count_empty_cell = need_delete;
   
   for (int i = 0; i < need_delete; i++) {
      int cell_c = rand() % (CELL_MAX - CELL_MIN) + CELL_MIN;
      int cell_r = rand() % (CELL_MAX - CELL_MIN) + CELL_MIN;
      
      // Check select Cell
      if (New_Puzzle[cell_c][cell_r] == 0) {
         while (!New_Puzzle[cell_c][cell_r]) {
            cell_c = rand() % (CELL_MAX - CELL_MIN) + CELL_MIN;
            cell_r = rand() % (CELL_MAX - CELL_MIN) + CELL_MIN;
         }
      }
      
      New_Puzzle[cell_c][cell_r] = 0;
   }
}

// Puzzle Getter
void Sudoku_Getter(int DIFFICULT) {
   // Random
   srand(time(NULL));
   
   // Create Puzzle
   generate_grid();
   
   // Transpose Puzzle
   Transpose_Puzzle();
   
   // Shuffle Puzzle
   int count_shuffle_coll = rand() % (SH_MAX - SH_MIN) + SH_MIN;
   int count_shuffle_row = rand() % (SH_MAX - SH_MIN) + SH_MIN;
   shuffle_row(count_shuffle_row);
   shuffle_coll(count_shuffle_coll);
   
   // Create Unresolved Grid Puzzle
   delete_cells(DIFFICULT);
   Dublicate_grid();
}

// Put nums in Puzzle on Game screen 
void put_nums() {
   char num_puzzle[4];
   
   for (int c = 0; c < P_SIZE; c++) {
      for (int r = 0; r < P_SIZE; r++) {
         if (Puzzle_Unresolved[c][r] != 0) {
            sprintf(num_puzzle, "%d", Puzzle_Unresolved[c][r]);
            outtextxy(X_BEGIN - 2 + SIZE_CELL * r +
                  ((SIZE_CELL - textwidth(num_puzzle)) / 2),
                        Y_BEGIN + 2 + SIZE_CELL * c +
                  ((SIZE_CELL - textheight(num_puzzle)) / 2),
                        num_puzzle);
         }
      }
   }
}

void drow_grid() {
   // Create Cube Grid
   setcolor(COLOR(147, 122, 71));
   rectangle(X_BEGIN, Y_BEGIN, X_BEGIN + SIZE_CELL * 9,
                  Y_BEGIN + SIZE_CELL * 9);
   
   // Create vertical line's
   for (int i = 1; i < P_SIZE; i++) {
      if (i % 3 != 0) {
         setcolor(COLOR(100, 100, 100));
         line(X_BEGIN + SIZE_CELL * i, Y_BEGIN,
               X_BEGIN + SIZE_CELL * i, Y_BEGIN + SIZE_CELL * 9);
      } else {
         setcolor(COLOR(147, 122, 71));
         line(X_BEGIN + SIZE_CELL * i, Y_BEGIN,
               X_BEGIN + SIZE_CELL * i, Y_BEGIN + SIZE_CELL * 9);
      }
   }

   // Create horizontal line's
   for (int i = 1; i < P_SIZE; i++) {
      if (i % 3 != 0) {
         setcolor(COLOR(100, 100, 100));
         line(X_BEGIN, Y_BEGIN + SIZE_CELL * i,
               X_BEGIN + SIZE_CELL * 9, Y_BEGIN + SIZE_CELL * i);
      } else {
         setcolor(COLOR(147, 122, 71));
         line(X_BEGIN, Y_BEGIN + SIZE_CELL * i,
               X_BEGIN + SIZE_CELL * 9, Y_BEGIN + SIZE_CELL * i);
      }
   }
   
   // Put nums on screen
   setcolor(COLOR(147, 122, 71));
   setbkcolor(COLOR(20, 20, 20));
   settextstyle(0, 0, 4);
   put_nums();
}

// Paint cell
void cell_paint(int X_SELECTED, int Y_SELECTED) {
   // Is it possible to change cell value
   if (X_SELECTED >= 0 && Y_SELECTED >= 0) {
      if (New_Puzzle[Y_SELECTED][X_SELECTED] != 0) {
         setcolor(COLOR(237, 2, 2));
      } else {
         setcolor(COLOR(255, 255, 255));
      }
      
      rectangle(X_BEGIN + SIZE_CELL * X_SELECTED,
            Y_BEGIN + SIZE_CELL * Y_SELECTED,
            X_BEGIN + SIZE_CELL + (SIZE_CELL * X_SELECTED),
            Y_BEGIN + SIZE_CELL + (SIZE_CELL * Y_SELECTED));
   }
}

// Is it possible to change cell value
bool check_select_cell(int c, int r) {
   if (New_Puzzle[c][r] == 0) {
      return 1;
   } else {
      return 0;
   }
}

// Victory check
int check_victory() {  
   // If Puzzle Full
   if (!count_empty_cell) {
      for (int c = 0; c < P_SIZE; c++) {
         for (int row_one = 0; row_one < P_SIZE; row_one++) {
            for (int row_two = 0; row_two < P_SIZE; row_two++) {
               if (row_one != row_two) {
                  // Horizontal
                  if (Puzzle_Unresolved[c][row_one] ==
               Puzzle_Unresolved[c][row_two]) {
                     // Lose
                     return 0;
                  }
                  // Vertical
                  if (Puzzle_Unresolved[row_one][c] ==
               Puzzle_Unresolved[row_two][c]) {
                     // Lose
                     return 0;
                  }                  
               }
            }
         }
      }
      
      // Win
      return 1;
   }
   
   return 2;
}

// Push num into Puzzle
void push_num_Puzzle(int key_pressed, int c, int r) {
   int num = 0;
   
   // Choose need num considering key_pressed
   switch (key_pressed) {
      case 49:
         num = 1; break;
      case 50:
         num = 2; break;
      case 51:
         num = 3; break;
      case 52:
         num = 4; break;
      case 53:
         num = 5; break;
      case 54:
         num = 6; break;
      case 55:
         num = 7; break;
      case 56:
         num = 8; break;
      case 57:
         num = 9; break;
   }
   
   // Edit Puzzle
   if (Puzzle_Unresolved[c][r] == 0) {
      count_empty_cell--;
   }
   Puzzle_Unresolved[c][r] = num;
   drow_grid();
   backlight_select_cell(true);
}

// Main function
void game(int DIFFICULT) {
   cleardevice();
   Sudoku_Getter(DIFFICULT);
}

