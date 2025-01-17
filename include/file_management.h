#pragma once

#include "./config.h"

#define CURRENT_GAME_FILE "../saves/grid.bin"
#define SOLUTION_FILE "../saves/solution.bin"

// Function used to save the sudoku grid to a text file
extern void save_sudoku_grid(uint8_t grid[9][9], const char *filename);

// Function used to load the sudoku grid from a text file
extern void load_sudoku_grid(uint8_t grid[9][9], const char *filename);