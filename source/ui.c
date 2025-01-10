#include "../include/ui.h"

void display_game_name() {
  system("cls");
  printf(BLUE BOLD UNDERLINE "\t\t=== %s ===\n\n" RESET, GAME_NAME);
}

void display_main_menu(uint8_t *main_menu_choice) {
  display_game_name();

  printf("1. New game\n");
  printf("2. Continue\n");
  printf("3. How to play\n");
  printf("4. Quit\n");
  printf(" >> ");
  if (scanf("%hhu", &(*main_menu_choice)) != 1)
    (*main_menu_choice) = 0;
  rewind(stdin);
}

void display_how_to_play() {
  display_game_name();
  printf(DARK_GREEN UNDERLINE "\t--- How to play ---\n\n" RESET);

  printf("1. The goal is to fill a 9x9 grid with numbers so that each row, column, \n");
  printf("   and 3x3 section contain all of the digits between 1 and 9.\n");
  printf("2. At the beginning of the game, some of the cells will be filled in.\n");
  printf("3. Use logic to fill in the missing digits.\n");
  printf("4. You can only use each number once in each row, column, and 3x3 section.\n");
  printf("5. The game is won when the entire grid is correctly filled.\n\n");
  printf("Game Levels:\n");
  printf("1. Easy: Suitable for beginners with more pre-filled cells.\n");
  printf("2. Medium: A moderate challenge with fewer pre-filled cells.\n");
  printf("3. Hard: The most difficult level with the least number of pre-filled cells.\n\n");

  printf(YELLOW);
  system("pause");
  printf(RESET);
}

void display_invalid_choice() {
  printf(ORANGE "Invalid choice. Please try again.\n" RESET);
  Sleep(4);
}