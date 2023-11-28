#ifndef GAME_H
#define GAME_H

// SIZE of Puzzle
const int P_SIZE = 9;
// Count Shuffle Coll and Row Puzzle 
const int SH_MIN = 3, SH_MAX = 10;
// Const of Shuffle algoritm
const int AREA_MIN = 0, AREA_MAX = 3; 
const int LINE_MIN = 0, LINE_MAX = 3;
const int CELL_MIN = 0, CELL_MAX = 9;
// Const of drawing Puzzle screen
const int X_BEGIN = 175, Y_BEGIN = 10;
const int SIZE_CELL = 50;

// Procedures
void game(int);
void drow_grid();
void push_num_Puzzle(int, int, int);
bool check_select_cell(int, int);
void cell_paint(int, int);
int check_victory();

#endif