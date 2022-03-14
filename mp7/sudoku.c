#include "sudoku.h"

/* MP7 Sudoku Solver - bmn4 ECE220 SP22
 * I filled out the 3 required functions (is_val_in_row, is_val_in_col, is_val_in_3x3_zone),
 * and created a helper function get_next_cell that gets the next empty cell
 * or returns 0 if board is solved.
 * I also implemented solve_sudoku using the flowchart in lab/class
 * 
 * Compiling with -Werror yields 2 incompatible pointer types (method wants const int array, we feed it in array)
 * I can't do anything without changing the given code so I'll leave it be
 */

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------

// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO

  //Check every item in row to see if it equals val
  for(int j = 0; j < 9; j++) {
    if(sudoku[i][j] == val) {
      return 1;
    }
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO

  //Check every item in col to see if it equals val
  for(int i = 0; i < 9; i++) {
    if(sudoku[i][j] == val) {
      return 1;
    }
  }
  
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO

  // Get coords of top left cell in 3x3 zone (only cell where both i and j are divisible by 3)
  int row_start = i / 3 * 3;
  int col_start = j / 3 * 3;

  // Check every cell in the 3x3 zone starting from top left to see if it equals val, if so return 1
  for(int row_offset = 0; row_offset < 3; row_offset++) {
    for(int col_offset = 0; col_offset < 3; col_offset++) {
      if(sudoku[row_start + row_offset][col_start + col_offset] == val) {
        return 1;
      }
    }
  }

  // If no matches, return 0  
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  // If any matches in col, row, or 3x3, it's an invalid guess
  if(is_val_in_col(val, j, sudoku) || is_val_in_row(val, i, sudoku) || is_val_in_3x3_zone(val, i, j, sudoku)) {
    return 0;
  }

  // If no matches, it's a valid guess, return 1
  return 1;
  // END TODO
}

// Function: get_next_cell
// Return true if there is an empty cell
// Stores coordinates of first empty cell in *empty_cell_row and *empty_cell_col
int get_next_cell(int *empty_cell_row, int *empty_cell_col, int sudoku[9][9]) {
  // Loop through sudoku grid, checking if each cell is empty
  for(int i = 0; i < 9; i++) {
    for(int j = 0; j < 9; j++) {
      if(sudoku[i][j] == 0) {
        // If empty, save to empty_cel_row and empty_cel_col and return 1
        *empty_cell_row = i;
        *empty_cell_col = j;

        return 1;
      }
    }
  }

  // If no empty cells, return 0
  return 0;
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {
  int i;
  int j;

  // BEG TODO.
  // Get next empty cell
  if(get_next_cell(&i, &j, sudoku)) {
    // Guess values 1-9 and check if they work
    for(int guess = 1; guess <= 9; guess++) {
      if(is_val_valid(guess, i, j, sudoku)) {
        // If value works, try to solve using that value there
        sudoku[i][j] = guess;

        if(solve_sudoku(sudoku)) {
          // If it's possible to solve with that value, return 1 (it's been solved)
          return 1;
        } else {
          // If the value is impossible to solve with, reset the cell and try next guess
          sudoku[i][j] = 0;
        }
      }
    }
  } else {
    // If not empty cells left, assume it's solved
    return 1;
  }

  // If no values work, sudoku unsolvable in current state
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





