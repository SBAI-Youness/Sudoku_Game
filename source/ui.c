#include "../include/ui.h"

void display_game_name() {
  system("cls");
  printf(BLUE BOLD UNDERLINE "\t\t=== %s ===\n\n" RESET, GAME_NAME);
}

void display_main_menu(uint8_t *main_menu_choice) {
  display_game_name();
  printf(DARK_GREEN BOLD "\t--- Main Menu ---\n\n" RESET);

  printf("1. New game\n");
  printf("2. Continue\n");
  printf("3. How to play?\n");
  printf("4. Quit\n");
  printf(" >> ");

  char extra;
  if (scanf("%hhu%c", &(*main_menu_choice), &extra) != 2 || extra != '\n') {
    (*main_menu_choice) = 0;
    clear_input_buffer();
  }
}

void display_game_mode_menu(uint8_t *game_mode_choice) {
  display_game_name();
  printf(DARK_GREEN BOLD "\t--- Select Difficulty ---\n\n" RESET);

  printf("1. Easy\n");
  printf("2. Medium\n");
  printf("3. Hard\n");
  printf("4. Back to Main Menu\n");
  printf(" >> ");

  char extra;
  if (scanf("%hhu%c", &(*game_mode_choice), &extra) != 2 || extra != '\n') {
    (*game_mode_choice) = 0;
    clear_input_buffer();
  }
}

void display_how_to_play() {
  display_game_name();
  printf(DARK_GREEN UNDERLINE "\t--- How to Play Sudoku ---\n\n" RESET);

  printf("Game Objective:\n");
  printf("- Fill the 9x9 grid with numbers 1-9 so that each row, column,\n");
  printf("  and 3x3 section contains all digits exactly once.\n\n");

  printf("Game Controls:\n");
  printf("- Enter row number (1-9)\n");
  printf("- Enter column number (1-9)\n");
  printf("- Enter the number you want to place (1-9)\n\n");

  printf("Game Rules:\n");
  printf("1. You have 3 attempts to complete the puzzle\n");
  printf("2. Each wrong number placement costs 1 attempt\n");
  printf("3. You cannot modify pre-filled cells\n");
  printf("4. The game ends when you either:\n");
  printf("   - Successfully complete the puzzle\n");
  printf("   - Run out of attempts\n\n");

  printf("Difficulty Levels:\n");
  printf("1. Easy: 61 pre-filled cells (20 cells removed)\n");
  printf("2. Medium: 41 pre-filled cells (40 cells removed)\n");
  printf("3. Hard: 21 pre-filled cells (60 cells removed)\n\n");

  printf("Tips:\n");
  printf("- Use '.' to identify empty cells on the grid\n");
  printf("- Your progress is automatically saved\n");
  printf("- You can continue your game later from the main menu\n\n");

  printf(YELLOW);
  system("pause");
  printf(RESET);
}

void display_invalid_choice() {
  printf(ORANGE "Invalid choice. Please try again.\n" RESET);
  sleep(INVALID_DELAY);
}

void display_invalid_input() {
  printf(ORANGE "Invalid input! Please enter a number between 1 and 9.\n" RESET);
  sleep(INVALID_DELAY);
  printf("\033[A\033[2K");
  printf("\033[A\033[2K");
}

void display_congratulations(double time_spent) {
  printf(GREEN "\nCongratulations! You solved the puzzle!\n" RESET);

  // Convert time to appropriate units
  if (time_spent < 60)
    printf("Time taken: %.0f seconds\n", time_spent);
  else if (time_spent < 3600)
    printf("Time taken: %.0f minutes and %.0f seconds\n", floor(time_spent/60), fmod(time_spent, 60));
  else
    printf("Time taken: %.0f hours, %.0f minutes and %.0f seconds\n",
           floor(time_spent/3600), 
           floor(fmod(time_spent, 3600)/60),
           fmod(time_spent, 60));

  sleep(GAME_OVER_AND_CONGRATULATIONS_DELAY);
}

void display_game_over() {
  printf(RED "\nGame Over! You've run out of attempts.\n" RESET);
  sleep(GAME_OVER_AND_CONGRATULATIONS_DELAY);
  return;
}