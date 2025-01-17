#include "../include/sudoku.h"

void generate_sudoku_puzzle(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t difficulty) {
  fill_grid(grid);
  save_sudoku_grid(grid, SOLUTION_FILE);
  remove_cells(grid, difficulty);
}

bool fill_grid(uint8_t grid[GRID_SIZE][GRID_SIZE]) {
  size_t row, col;
  bool found_empty = false; // Flag to indicate if an empty cell was found

  // Find first empty cell
  for (row = 0; row < GRID_SIZE && found_empty == false; row++) {
    for (col = 0; col < GRID_SIZE && found_empty == false; col++)
      if (grid[row][col] == 0) {
        found_empty = true; // Set flag to true, because an empty cell was found
        break; // Exit the inner loop
      }
    if (found_empty)
      break; // Exit the outer loop
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
  // Map difficulty directly to cells to remove
  static const size_t difficulty_map[] = {
    0,                      // unused
    CELLS_TO_REMOVE_EASY,   // difficulty 1
    CELLS_TO_REMOVE_MEDIUM, // difficulty 2
    CELLS_TO_REMOVE_HARD    // difficulty 3
  };

  size_t cells_to_remove = difficulty_map[difficulty];

  // Create an array of all valid cell positions
  size_t positions[GRID_SIZE * GRID_SIZE];
  for (size_t i = 0; i < GRID_SIZE * GRID_SIZE; i++)
    positions[i] = i;

  // Fisher-Yates shuffle to randomize cell removal order
  for (size_t i = GRID_SIZE * GRID_SIZE - 1; i > 0; i--) {
    size_t j = rand() % (i + 1),
           temp = positions[i];
    positions[i] = positions[j];
    positions[j] = temp;
  }

  // Remove cells using the shuffled positions
  for (size_t i = 0; i < cells_to_remove; i++) {
    size_t pos = positions[i],
           row = pos / GRID_SIZE,
           col = pos % GRID_SIZE;
    grid[row][col] = 0;
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

bool is_puzzle_solved(uint8_t grid[GRID_SIZE][GRID_SIZE]) {
  for (size_t row = 0; row < GRID_SIZE; row++)
    for (size_t col = 0; col < GRID_SIZE; col++)
      if (grid[row][col] == 0)
        return false;

  return true;
}

void display_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE], bool user_filled[GRID_SIZE][GRID_SIZE]) {
  printf("\n    1 2 3   4 5 6   7 8 9\n");  // Column numbers
  printf("  +-------+-------+-------+\n");

  for (int row = 0; row < GRID_SIZE; row++) {
    printf("%d ", row + 1);  // Row numbers

    for (int col = 0; col < GRID_SIZE; col++) {
      if (col % 3 == 0)
        printf("| ");

      if (grid[row][col] == 0)
        printf(". ");
      else {
        // Check if this cell was filled by the user
        if (user_filled[row][col] == true)
          printf(BLUE "%d " RESET, grid[row][col]);
        else
          printf("%d ", grid[row][col]);
      }
    }
    printf("|\n");

    if ((row + 1) % 3 == 0 && row < GRID_SIZE - 1)
      printf("  +-------+-------+-------+\n");
  }

  printf("  +-------+-------+-------+\n\n");
}