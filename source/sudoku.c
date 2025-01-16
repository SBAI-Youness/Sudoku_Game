#include "../include/sudoku.h"

void sudoku_game() {
  uint8_t main_menu_choice;

  srand(time(NULL));

  do {
    display_main_menu(&main_menu_choice);

    switch (main_menu_choice) {
      case 1: // New game
        new_game();
        break;
      case 2: // Continue game
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
  } while (main_menu_choice != 4); // Loop until the user chooses to quit
}

void new_game() {
  uint8_t game_mode_choice, // Variable to store the user's choice of game mode
          grid[GRID_SIZE][GRID_SIZE] = {0}; // Initialize the grid with zeros

  do {
    display_game_mode_menu(&game_mode_choice);

    switch (game_mode_choice) {
      case 1:
      case 2:
      case 3: // Easy, Medium, Hard
        generate_sudoku_puzzle(grid, game_mode_choice); // Generate a new and random sudoku puzzle
        save_sudoku_grid(grid, CURRENT_GAME_FILE); // Save the puzzle to a file for later use
        play_game(grid); // Play the game
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
}

void play_game(uint8_t grid[GRID_SIZE][GRID_SIZE]) {
  uint8_t solution[GRID_SIZE][GRID_SIZE]; // 2D array to store the solution of the sudoku puzzle
  uint8_t user_filled[GRID_SIZE][GRID_SIZE] = {0}; // Track user-filled cells

  // Load the solution of the sudoku puzzle from a file
  load_sudoku_grid(solution, SOLUTION_FILE);

  uint8_t row, column, number; // Variables to store the user's input
  char extra; // Variable to store the extra character after the user input
  size_t attempts_left = MAX_ATTEMPTS; // Variable to store the number of attempts left
  time_t start_time = time(NULL); // Variable to store the start time of the game

  // Loop until the user solves the puzzle or runs out of attempts
  while (attempts_left > 0) {
    display_game_name();
    display_sudoku_grid(grid, user_filled);

    printf("Attempts remaining:" ORANGE " %zu\n" RESET, attempts_left);

    // Input for Row
    printf("Enter row (1-9): ");
    while (scanf("%hhu%c", &row, &extra) != 2 || extra != '\n' || row < 1 || row > GRID_SIZE) {
      display_invalid_input();
      printf("Enter row (1-9): ");
    }

    // Input for Column
    printf("Enter column (1-9): ");
    while (scanf("%hhu%c", &column, &extra) != 2 || extra != '\n' || column < 1 || column > GRID_SIZE) {
      printf("Enter column (1-9): ");
      display_invalid_input();
    }

    // Adjust for zero-based indexing
    row--;
    column--;

    // Check if cell is empty
    if (grid[row][column] != 0) {
      printf(ORANGE "This cell is already filled!\n" RESET);
      sleep(INVALID_DELAY);
      continue;
    }

    // Input for Number
    printf("Enter number (1-9): ");
    while (scanf("%hhu%c", &number, &extra) != 2 || extra != '\n' || number < 1 || number > 9) {
      display_invalid_input();
      printf("Enter number (1-9): ");
    }

    // Check if number is correct
    if (solution[row][column] == number) {
      grid[row][column] = number;
      user_filled[row][column] = 1; // Mark this cell as user-filled
      save_sudoku_grid(grid, CURRENT_GAME_FILE);

      if (is_puzzle_solved(grid) == true) {
        time_t end_time = time(NULL);
        double time_spent = difftime(end_time, start_time);

        display_game_name();
        display_sudoku_grid(grid, user_filled);

        display_congratulations(time_spent);
      }
    }
    else {
      printf(ORANGE "Wrong number! Try again.\n" RESET);
      sleep(INVALID_DELAY);
      attempts_left--;

      if (attempts_left == 0)
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
    size_t pos = positions[i];
    size_t row = pos / GRID_SIZE;
    size_t col = pos % GRID_SIZE;
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

void display_sudoku_grid(uint8_t grid[GRID_SIZE][GRID_SIZE], uint8_t user_filled[GRID_SIZE][GRID_SIZE]) {
  printf("\n");
  printf("    1 2 3   4 5 6   7 8 9\n");  // Column numbers
  printf("  +-------+-------+-------+\n");

  for (int row = 0; row < GRID_SIZE; row++) {
    printf("%d ", row + 1);  // Row numbers

    for (int col = 0; col < GRID_SIZE; col++) {
      if (col % 3 == 0)
        printf("| ");

      if (grid[row][col] == 0) {
        printf(". ");
      } else {
        // Check if this cell was filled by the user
        if (user_filled[row][col]) {
          printf(BLUE "%d " RESET, grid[row][col]);
        } else {
          printf("%d ", grid[row][col]);
        }
      }
    }
    printf("|\n");

    if ((row + 1) % 3 == 0 && row < GRID_SIZE - 1)
      printf("  +-------+-------+-------+\n");
  }

  printf("  +-------+-------+-------+\n\n");
}

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
    display_error_message("Error writing to the file");

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
    display_error_message("Error reading from the file");

  // Close file
  if (fclose(file) != 0)
    display_error_message("Could not close the file");
}