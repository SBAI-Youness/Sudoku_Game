#include "../include/config.h"

int main() {
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

  return EXIT_SUCCESS;
}