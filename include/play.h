#pragma once

#include "./config.h"
#include "./process.h"
#include "./render.h"

// Function used to handle the process of the game while playing
extern void HandlePlayingProcess(struct Player *player, enum GAME_STATE *game_state, enum GAME_DIFFICULTY *game_difficulty, Texture2D pause_image_texture);

// Function used to generate a sudoku grid based on the difficulty using the backtracking algorithm
extern void GenerateSudokuGrid(struct Cell grid[GRID_SIZE][GRID_SIZE], enum GAME_DIFFICULTY game_difficulty);

// Function used to generate a valid full grid
extern bool FillGrid(struct Cell grid[GRID_SIZE][GRID_SIZE]);

// Function used to check if a given number in the grid is valid or not
extern bool IsSafe(struct Cell grid[GRID_SIZE][GRID_SIZE], int row, int column, int number);

// Function used to check if the player's move is correct or not
extern bool IsMoveCorrect(int row, int column, int number);

// Function used to check if the puzzle was solved or not
extern bool is_puzzle_solved(struct Cell grid[GRID_SIZE][GRID_SIZE]);

// Function used to remove cells from a sudoku grid based on the difficulty level
extern void RemoveCells(struct Cell grid[GRID_SIZE][GRID_SIZE], enum GAME_DIFFICULTY game_difficulty);

// Function used to save the state of a game
extern bool SaveGameState(struct Player *player, enum GAME_DIFFICULTY game_difficulty, struct Cell grid[GRID_SIZE][GRID_SIZE]);

// Function used to load the state of a played game
extern bool LoadGameState(struct Player *player, enum GAME_DIFFICULTY *game_difficulty, struct Cell grid[GRID_SIZE][GRID_SIZE]);

// Function used to delete the state of played game
extern bool DeleteGameState(struct Player *player);
