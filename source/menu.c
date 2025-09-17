#include "../include/menu.h"

static bool DoesSaveExist(struct Player *player) {
  char file_path[256];
  snprintf(file_path, sizeof(file_path), "%s%s.txt", GAME_STATE_SAVE_DIRECTORY, player->name);

  FILE *file = fopen(file_path, "r");

  if (file == NULL) {
    return false;
  }

  fclose(file);
  return true;
}

static bool show_no_save_message = false;

void HandleGameMenuProcess(struct Player *player, enum GAME_STATE *game_state, Texture2D game_icon_texture) {
  // Define the text for each menu option
  const char *game_menu_option[] = { "New Game",
                                     "Continue Game",
                                     "How to Play",
                                     "Log Out"};

  // Count how many menu items exist
  int menu_count = sizeof(game_menu_option) / sizeof(game_menu_option[0]);

  // Store each menu option's clickable area as a Rectangle
  Rectangle menu_buttons[menu_count];

  static int selected_button = -1;

  // Layout settings
  int start_y = 200, // Where the first option will be drawn vertically
      spacing = 60,  // Vertical spacing between menu items
      button_width = 250, // Fixed width for all buttons
      button_height = 50; // Fixed height for all buttons

  // Precompute button rectangles for each menu option
  for (int i = 0; i < menu_count; i++) {
    int button_x = (WINDOW_WIDTH / 2) - (button_width / 2),
        button_y = start_y + (i * spacing);

    // Save button rectangle for drawing and input detection
    menu_buttons[i] = (Rectangle) { button_x, button_y, button_width, button_height};
  }

  // Process the input for the game menu
  ProcessGameMenuInput(player, game_state, menu_buttons, menu_count, &selected_button);

  // Render the game menu with the appropriate elements (game menu options)
  RenderGameMenuPage(game_icon_texture, menu_buttons, game_menu_option, menu_count, selected_button);

  // Draw warning message if there is no save to continue
  if (show_no_save_message == true) {
    const char *message = "No previous saved game to continue!";
    int tw = MeasureText(message, 18);
    int text_y = start_y + (menu_count * spacing) + 8;

    DrawText(message, (WINDOW_WIDTH - tw) / 2, text_y, 18, RED);
  }
}

void HandleGameMenuAction(struct Player *player, enum GAME_STATE *game_state, int selected_button) {
  switch (selected_button) {
    case 0: // "New Game"
      player->resume_requested = false;
      show_no_save_message = false;
      ChangeGameState(game_state, MODE_MENU);
      break;

    case 1: // "Continue Game"
      if (DoesSaveExist(player) == false) {
        show_no_save_message = true;
        ChangeGameState(game_state, MAIN_MENU);
      }
      else {
        show_no_save_message = false;
        player->resume_requested = true;
        ChangeGameState(game_state, PLAYING);
      }
      break;

    case 2: // "How to Play"
      show_no_save_message = false;
      ChangeGameState(game_state, TUTORIAL);
      break;

    case 3: // "Log Out"
      show_no_save_message = false;
      player->resume_requested = false;
      player->name[0] = '\0';
      player->password[0] = '\0';
      ChangeGameState(game_state, SIGN_UP);
      break;
  }
}
