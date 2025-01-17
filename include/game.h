#pragma once

#include "./config.h"

// Main function of the game
extern void sudoku_game();

// Function used to start a new game
extern void new_game();

// Function used to continue a saved game
extern void continue_game();

// Function used to play the game
extern void play_game(uint8_t grid[9][9]);