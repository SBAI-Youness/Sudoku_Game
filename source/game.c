#include "../include/game.h"

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
      case 4: // Back to the main menu
        break;
      default: // Invalid choice
        display_invalid_choice();
        break;
    }
  } while (game_mode_choice != 4); // Loop until the user chooses to go back to the main menu
}

void continue_game() {
  uint8_t grid[GRID_SIZE][GRID_SIZE]; // 2D array to store the sudoku puzzle

  load_sudoku_grid(grid, CURRENT_GAME_FILE); // Load the sudoku puzzle from a file

  if (is_puzzle_solved(grid) == true) // Check if the puzzle is already solved
    return; // Puzzl is already solved, so we don't need to play the game

  // Play the game
  play_game(grid);
}

void play_game(uint8_t grid[GRID_SIZE][GRID_SIZE]) {
  uint8_t solution[GRID_SIZE][GRID_SIZE]; // 2D array to store the solution of the sudoku puzzle
  bool user_filled[GRID_SIZE][GRID_SIZE] = {false}; // Track user-filled cells

  // Load the solution of the sudoku puzzle from a file
  load_sudoku_grid(solution, SOLUTION_FILE);

  uint8_t row, column, number; // Variables to store the user's input
  size_t attempts_left = MAX_ATTEMPTS; // Variable to store the number of attempts left
  time_t start_time = time(NULL); // Variable to store the start time of the game

  // Loop until the user solves the puzzle or runs out of attempts
  while (attempts_left > 0) {
    display_game_name();
    display_sudoku_grid(grid, user_filled);

    printf("Attempts remaining:" ORANGE " %zu\n" RESET, attempts_left);

    // Input for Row
    do {
      printf("Enter row (1-9): ");
    } while (read_user_input(&row) == false || row < 1 || row > GRID_SIZE);

    // Input for Column
    do {
      printf("Enter column (1-9): ");
    } while (read_user_input(&column) == false || column < 1 || column > GRID_SIZE);

    // Adjust for zero-based indexing
    row--;
    column--;

    // Check if cell is empty
    if (grid[row][column] != 0) {
      printf(ORANGE "This cell is already filled!\n" RESET);
      sleep(DISPLAY_DELAY);
      continue;
    }

    // Input for Number
    do {
      printf("Enter number (1-9): ");
    } while (read_user_input(&number) == false || number < 1 || number > GRID_SIZE);

    // Check if the number is correct
    if (solution[row][column] != number) {
      printf(ORANGE "Wrong number! Try again.\n" RESET);
      sleep(DISPLAY_DELAY);
      attempts_left--;

      // If the user has no more attempts left, display the game over message
      if (attempts_left == 0)
        display_game_over();

      continue;
    }

    grid[row][column] = number;
    user_filled[row][column] = true; // Mark this cell as user-filled

    save_sudoku_grid(grid, CURRENT_GAME_FILE);

    if (is_puzzle_solved(grid) == true) {
      time_t end_time = time(NULL);
      double time_spent = difftime(end_time, start_time);

      display_game_name();
      display_sudoku_grid(grid, user_filled);

      display_congratulations(time_spent);
      return;
    }
  }
}