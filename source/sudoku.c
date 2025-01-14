#include "../include/sudoku.h"

void new_game() {
  uint8_t game_mode_choice,
          grid[GRID_SIZE][GRID_SIZE] = {0};

  do {
    display_game_mode_menu(&game_mode_choice);

    switch (game_mode_choice) {
      case 1:
      case 2:
      case 3:
        generate_sudoku_puzzle(grid, game_mode_choice);
        display_sudoku_grid(grid);
        break;
      case 4: // Back
        break;
      default: // Invalid choice
        display_invalid_choice();
        break;
    }
  } while (game_mode_choice != 4); // Loop until the user chooses to go back to the main menu
}

void generate_sudoku_puzzle(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t difficulty) {
  fill_grid(grid);
  remove_cells(grid, difficulty);
}

bool fill_grid(uint8_t grid[GRID_SIZE][GRID_SIZE]) {
  size_t row, col;
  bool found_empty = false;

  // Find first empty cell
  for (row = 0; row < GRID_SIZE && found_empty == false; row++) {
    for (col = 0; col < GRID_SIZE && found_empty == false; col++)
      if (grid[row][col] == 0) {
        found_empty = true;
        break;
      }
    if (found_empty)
      break;
  }

  // If no empty cell found, puzzle is complete
  if (found_empty == false)
    return true; // Puzzle is complete

  // Try filling the empty cell
  uint8_t numbers[GRID_SIZE];
  for (uint8_t i = 0; i < GRID_SIZE; i++)
    numbers[i] = i + 1;

  // Shuffle numbers
  for (uint8_t i = 0; i < GRID_SIZE; i++) {
    uint8_t j = rand() % GRID_SIZE;
    uint8_t temp = numbers[i];
    numbers[i] = numbers[j];
    numbers[j] = temp;
  }

  // Try each number
  for (uint8_t i = 0; i < GRID_SIZE; i++)
    if (is_valid(grid, row, col, numbers[i])) {
      grid[row][col] = numbers[i];
      if (fill_grid(grid))
        return true; // Puzzle is complete
      grid[row][col] = 0;
    }

  return false; // No number worked, backtrack
}

void remove_cells(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t difficulty) {
  size_t cells_to_remove;

  switch (difficulty) {
    case 1: // Easy
      cells_to_remove = 20;
      break;
    case 2: // Medium
      cells_to_remove = 40;
      break;
    case 3: // Hard
      cells_to_remove = 60;
      break;
  }

  size_t attempts = 0,
         max_attempts = GRID_SIZE * GRID_SIZE * 2;  // Maximum tries = 2 * total cells

  while (cells_to_remove > 0 && attempts < max_attempts) {
    size_t row = rand() % GRID_SIZE,
           col = rand() % GRID_SIZE;
    if (grid[row][col] != 0) {
      grid[row][col] = 0;
      cells_to_remove--;
    }
    attempts++;
  }
}

bool is_valid(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t row, uint8_t col, uint8_t num) {
  for (size_t x = 0; x < GRID_SIZE; x++)
    if (grid[row][x] == num || grid[x][col] == num)
      return false; // Number already exists in row or column

  size_t startRow = row - row % SUB_GRID_SIZE,
         startCol = col - col % SUB_GRID_SIZE;
  for (size_t i = 0; i < SUB_GRID_SIZE; i++)
    for (size_t j = 0; j < SUB_GRID_SIZE; j++)
      if (grid[startRow + i][startCol + j] == num)
        return false; // Number already exists in sub-grid

  return true; // Number is valid
}

void display_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE]) {
  for (size_t row = 0; row < GRID_SIZE; row++) {
    for (size_t col = 0; col < GRID_SIZE; col++)
      printf("%hhu ", grid[row][col]);
    printf("\n");
  }

  //! This is just for testing purposes
  system("pause");
}