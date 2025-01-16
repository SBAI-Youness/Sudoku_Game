#pragma once

#include "./config.h"

#define CURRENT_GAME_FILE "../saves/grid.bin"
#define SOLUTION_FILE "../saves/solution.bin"

#define GRID_SIZE 9
#define SUB_GRID_SIZE 3

// Main function of the game
extern void sudoku_game();

// Function used to start a new game
extern void new_game();

// Function used to continue a saved game
extern void continue_game();

// Function used to play the game
extern void play_game(uint8_t grid[GRID_SIZE][GRID_SIZE]);

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
extern void display_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE]);

// Function used to save the sudoku grid to a text file
extern void save_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE], const char *filename);

// Function used to load the sudoku grid from a text file
extern void load_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE], const char *filename);