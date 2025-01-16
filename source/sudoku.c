#include "../include/sudoku.h"

void sudoku_game() {
  uint8_t main_menu_choice;

  srand(time(NULL));

  do {
    display_main_menu(&main_menu_choice);

    switch (main_menu_choice) {
      case 1:
        new_game();
        break;
      case 2:
        continue_game();
        break;
      case 3: // Display the rules of the game
        display_how_to_play();
        break;
      case 4: // Quit
        break;
      default: // Invalid choice
        display_invalid_choice();
        break;
    }
  } while (main_menu_choice != 4);
}

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
        save_sudoku_grid(grid, CURRENT_GAME_FILE);
        play_game(grid);
        break;
      case 4: // Back
        break;
      default: // Invalid choice
        display_invalid_choice();
        break;
    }
  } while (game_mode_choice != 4); // Loop until the user chooses to go back to the main menu
}

void continue_game() {
  uint8_t grid[GRID_SIZE][GRID_SIZE];

  load_sudoku_grid(grid, CURRENT_GAME_FILE);

  play_game(grid);
}

void play_game(uint8_t grid[GRID_SIZE][GRID_SIZE]) {
  uint8_t solution[GRID_SIZE][GRID_SIZE];

  load_sudoku_grid(solution, SOLUTION_FILE);

  uint8_t row, col, number;
  int attempts = 3;
  time_t start_time = time(NULL);

  while (attempts > 0) {
    // Display the sudoku grid
    display_game_name();
    display_sudoku_grid(grid);
    printf("Attempts remaining: %d\n", attempts);

    char extra;

    // Input for Row
    printf("Enter row (1-9): ");
    if (scanf("%hhu%c", &row, &extra) != 2 || extra != '\n' || row < 1 || row > GRID_SIZE) {
      display_invalid_input();
      continue;
    }

    // Input for Column
    printf("Enter column (1-9): ");
    if (scanf("%hhu%c", &col, &extra) != 2 || extra != '\n' || col < 1 || col > GRID_SIZE) {
      display_invalid_input();
      continue;
    }

    // Adjust for zero-based indexing
    row--;
    col--;

    // Check if cell is empty
    if (grid[row][col] != 0) {
      printf(ORANGE "This cell is already filled!\n" RESET);
      sleep(3);
      continue;
    }

    // Input for Number
    printf("Enter number (1-9): ");
    if (scanf("%hhu%c", &number, &extra) != 2 || extra != '\n' || number < 1 || number > 9) {
      display_invalid_input();
      continue;
    }

    // Check if number is correct
    if (solution[row][col] == number) {
      grid[row][col] = number;
      save_sudoku_grid(grid, CURRENT_GAME_FILE);

      if (is_puzzle_solved(grid)) {
        time_t end_time = time(NULL);
        double time_spent = difftime(end_time, start_time);

        display_game_name();
        display_sudoku_grid(grid);
        printf("\nCongratulations! You solved the puzzle!\n");

        // Convert time to appropriate units
        if (time_spent < 60) 
          printf("Time taken: %.0f seconds\n", time_spent);
        else if (time_spent < 3600) {
          printf("Time taken: %.0f minutes and %.0f seconds\n", 
          floor(time_spent/60), fmod(time_spent, 60));
        }
        else {
          printf("Time taken: %.0f hours, %.0f minutes and %.0f seconds\n",
          floor(time_spent/3600), 
          floor(fmod(time_spent, 3600)/60),
          fmod(time_spent, 60));
        }
        sleep(3);
        return;
      }
    }
    else {
      printf(ORANGE "Wrong number! Try again.\n" RESET);
      sleep(3);
      attempts--;

      if (attempts == 0)
        display_game_over();
    }
  }
}

void generate_sudoku_puzzle(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t difficulty) {
  fill_grid(grid);
  save_sudoku_grid(grid, SOLUTION_FILE);
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

bool is_puzzle_solved(uint8_t grid[GRID_SIZE][GRID_SIZE]) {
  for (size_t row = 0; row < GRID_SIZE; row++)
    for (size_t col = 0; col < GRID_SIZE; col++)
      if (grid[row][col] == 0)
        return false;

  return true;
}

void display_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE]) {
  printf("\n");
  printf("    1 2 3   4 5 6   7 8 9\n");  // Column numbers
  printf("  +-------+-------+-------+\n");

  for (int row = 0; row < GRID_SIZE; row++) {
    printf("%d ", row + 1);  // Row numbers

    for (int col = 0; col < GRID_SIZE; col++) {
      if (col % 3 == 0)
        printf("| ");

      if (grid[row][col] == 0)
        printf(". ");
      else
        printf("%d ", grid[row][col]);
    }
    printf("|\n");

    if ((row + 1) % 3 == 0 && row < GRID_SIZE - 1)
      printf("  +-------+-------+-------+\n");
  }

  printf("  +-------+-------+-------+\n\n");
}

void save_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE], const char *filename) {
  // Open the file for writing
  FILE* file = fopen(filename, "w");

  // Check if the file was opened successfully
  if (file == NULL) {
    fprintf(stderr, "Error: Could not create the grid file!\n");
    return;
  }

  // Write the grid to the file
  for (size_t row = 0; row < GRID_SIZE; row++) {
    for (size_t col = 0; col < GRID_SIZE; col++) {
      fprintf(file, "%hhu", grid[row][col]);
      if (col < GRID_SIZE - 1)
        fprintf(file, " "); // Add space between numbers
    }
    fprintf(file, "\n"); // New line after each row
  }

  // Close the file
  fclose(file);
}

void load_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE], const char *filename) {
  // Open file for reading
  FILE *file = fopen(filename, "r");

  // Check if file exists
  if (file == NULL) {
    fprintf(stderr, "Error: Could not open file!\n");
    return;
  }

  // Read grid from file
  for (size_t row = 0; row < GRID_SIZE; row++)
    for (size_t col = 0; col < GRID_SIZE; col++)
      if (fscanf(file, "%hhu", &grid[row][col]) != 1) {
        printf("\nError reading saved game!\n");
        fclose(file);
        system("pause");
        return;
      }

  // Close file
  fclose(file);
}