#pragma once

#include "./config.h"

// Path to the saved game file
#define SUDOKU_GRID_FILE "../saved_game/grid.txt"

#define GRID_SIZE 9
#define SUB_GRID_SIZE 3

// Function used to start a new game
extern void new_game();

// Function used to generate a randow sudoku puzzle
extern void generate_sudoku_puzzle(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t difficulty);

// Function used to fill a sudoku grid with random numbers using recursive backtracking
extern bool fill_grid(uint8_t grid[GRID_SIZE][GRID_SIZE]);

// Function used to remove cells from a sudoku grid based on the difficulty level
extern void remove_cells(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t difficulty);

// Function used to check if a number is valid in a sudoku grid
extern bool is_valid(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t row, uint8_t col, uint8_t num);

// Function used to display the sudoku grid
extern void display_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE]);

// Function used to save the sudoku grid to a text file
extern void save_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE]);