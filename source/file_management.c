#include "../include/file_management.h"

void save_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE], const char *filename) {
  // Open the file for writing
  FILE* file = fopen(filename, "wb");

  // Check if the file was opened successfully
  if (file == NULL) {
    display_error_message("Could not open the file for writing");
    return;
  }

  // Write the grid to the file
  if (fwrite(grid, sizeof(uint8_t), GRID_SIZE * GRID_SIZE, file) != GRID_SIZE * GRID_SIZE)
    display_error_message("Could not write to the file");

  // Close the file
  if (fclose(file) != 0)
    display_error_message("Could not close the file");
}

void load_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE], const char *filename) {
  // Open file for reading
  FILE *file = fopen(filename, "r");

  // Check if file exists
  if (file == NULL) {
    display_error_message("Could not open the file for reading");
    return;
  }

  // Read grid from file
  if (fread(grid, sizeof(uint8_t), GRID_SIZE * GRID_SIZE, file) != GRID_SIZE * GRID_SIZE)
    display_error_message("Could not read from the file");

  // Close file
  if (fclose(file) != 0)
    display_error_message("Could not close the file");
}