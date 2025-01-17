#pragma once

#include "./config.h"

#define GRID_SIZE 9
#define SUB_GRID_SIZE 3

#define MAX_ATTEMPTS 3

#define CELLS_TO_REMOVE_EASY 20
#define CELLS_TO_REMOVE_MEDIUM 40
#define CELLS_TO_REMOVE_HARD 60

// Function used to generate a randow sudoku puzzle
extern void generate_sudoku_puzzle(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t difficulty);

// Function used to fill a sudoku grid with random numbers using the recursive backtracking algorithm
extern bool fill_grid(uint8_t grid[GRID_SIZE][GRID_SIZE]);

// Function used to remove cells from a sudoku grid based on the difficulty level
extern void remove_cells(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t difficulty);

// Function used to check if a number is valid in a sudoku grid
extern bool is_valid(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t row, uint8_t col, uint8_t num);

// Function used to check if a sudoku puzzle is solved
extern bool is_puzzle_solved(uint8_t grid[GRID_SIZE][GRID_SIZE]);

// Function used to display the sudoku grid
extern void display_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE], bool user_filled[GRID_SIZE][GRID_SIZE]);