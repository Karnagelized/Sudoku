#include <iostream>
#include <ctime>

// SIZE of Puzzle
const int SIZE = 9;
// Count Shuffle Coll and Row Puzzle 
const int SH_MIN = 3, SH_MAX = 10;
// Const of Shuffle algoritm
const int AREA_MIN = 0, AREA_MAX = 3; 
const int LINE_MIN = 0, LINE_MAX = 3;
// Difficult(0 - EASY, 1 - NORMAL 2 - HARD)
const int DIFFICLUT = 2;
const int CELL_MIN = 0, CELL_MAX = 9;

// Var
int Empty_Puzzle[SIZE][SIZE] = {0};
int count_invalid_values = 0;

using namespace std;

// Print Sudoku
void print_Puzzle(int **Puzzle) {
   for (int c = 0; c < SIZE; c++) {
      for (int r = 0; r < SIZE; r++) {
         cout << Puzzle[c][r] << " ";
      }
      cout << endl;
   }
   cout << endl;
}

// Generate Correct Grid Sudoku
int** generate_grid() {
   int **New_Puzzle;
   New_Puzzle = new int*[SIZE];

   for(int i = 0; i < SIZE; i++) {
      New_Puzzle[i] = new int[SIZE];
   }
   
   for (int r = 0; r < SIZE; r++) {
      for (int c = 0; c < SIZE; c++) {
         New_Puzzle[r][c] = (r * (SIZE/3) + r/(SIZE/3) + c) % SIZE + 1;
      }
   }
   return New_Puzzle;
}

// Transpose Grid Puzzle
void Transpose_Puzzle(int **Puzzle) {
   int t;
   for(int c = 0; c < SIZE; ++c) {
      for(int r = c; r < SIZE; ++r) {
         t = Puzzle[c][r];
         Puzzle[c][r] = Puzzle[r][c];
         Puzzle[r][c] = t;
      }
   }
}

// Shuffle collum
void shuffle_row(int **Puzzle, int count_shuffle) {
   for (int i = 0; i < count_shuffle; i++) {
      int temp = 0;
      int area = rand() % (AREA_MAX - AREA_MIN) + AREA_MIN;
      int temp_line1 = rand() % (LINE_MAX - LINE_MIN) + LINE_MIN;
      int temp_line2 = rand() % (LINE_MAX - LINE_MIN) + LINE_MIN;
      int first_line = area * (SIZE/3) + temp_line1;
      
      // Check equality line's
      while(temp_line1 == temp_line2) {
         temp_line2 = rand() % (LINE_MAX - LINE_MIN) + LINE_MIN;
      }
      int second_line = area * (SIZE/3) + temp_line2;
      /*
      cout << "\nAREA: " << area << endl;
      cout << "\nLINES : " << first_line << " " << second_line << endl;
      */
      if (first_line != second_line) {
         for (int n = 0; n < SIZE; n++) {
            int temp = Puzzle[first_line][n];
            Puzzle[first_line][n] = Puzzle[second_line][n];
            Puzzle[second_line][n] = temp;
         }
      }
      /*
      print_Puzzle(Puzzle);
      cout << endl;
      */
   }
}

// Shuffle row
void shuffle_coll(int **Puzzle, int count_shuffle) {
   for (int i = 0; i < count_shuffle; i++) {
      Transpose_Puzzle(Puzzle);
      shuffle_row(Puzzle, 1);
      Transpose_Puzzle(Puzzle);
   }
}

//Dublicate Grid Puzzle
int** Dublicate_grid(int **Puzzle) {
   int **Dublicate_Puzzle;
   Dublicate_Puzzle = new int*[SIZE];

   for(int i = 0; i < SIZE; i++) {
      Dublicate_Puzzle[i] = new int[SIZE];
   }
   
   for (int r = 0; r < SIZE; r++) {
      for (int c = 0; c < SIZE; c++) {
         Dublicate_Puzzle[r][c] = Puzzle[r][c];
      }
   }
   return Dublicate_Puzzle;
}

void delete_cells(int **Puzzle) {
   int need_delete = 30; // EASY DIFFICULT
   
   if (DIFFICLUT == 1) {
      need_delete = 35; //NORMAL DIFFICULT
   } else if (DIFFICLUT == 2) {
      need_delete = 40; // HARD DIFFICULT
   }

   for (int i = 0; i < need_delete; i++) {
      int cell_c = rand() % (CELL_MAX - CELL_MIN) + CELL_MIN;
      int cell_r = rand() % (CELL_MAX - CELL_MIN) + CELL_MIN;
      
      // Check select Cell
      if (Puzzle[cell_c][cell_r] == 0) {
         while (!Puzzle[cell_c][cell_r]) {
            cell_c = rand() % (CELL_MAX - CELL_MIN) + CELL_MIN;
            cell_r = rand() % (CELL_MAX - CELL_MIN) + CELL_MIN;
         }
      }
      
      Puzzle[cell_c][cell_r] = 0;
   }
}

// Main Function
int main() {
   // Random
   srand(time(NULL));
   
   // Create Puzzle
   cout << "New Grid:\n";
   int **Puzzle_grid = generate_grid();
   
   // Transpose Puzzle
   cout << "Transpose Puzzle:\n";
   Transpose_Puzzle(Puzzle_grid);
   //print_Puzzle(Puzzle_grid);
   
   // Shuffle Puzzle
   int count_shuffle_coll = rand() % (SH_MAX - SH_MIN) + SH_MIN;
   int count_shuffle_row = rand() % (SH_MAX - SH_MIN) + SH_MIN;
   shuffle_row(Puzzle_grid, count_shuffle_row);
   shuffle_coll(Puzzle_grid, count_shuffle_coll);
   
   cout << "Final Grid Sudoku:\n";
   print_Puzzle(Puzzle_grid);
   
   // Create Unresolved Grid Puzzle
   int **Puzzle_Unresolved = Dublicate_grid(Puzzle_grid);
   delete_cells(Puzzle_Unresolved);
   
   cout << "Unresolved Grid Sudoku:\n";
   print_Puzzle(Puzzle_Unresolved);
   
   return 0;
}

