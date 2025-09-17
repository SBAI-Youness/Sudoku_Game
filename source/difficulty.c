#include "../include/difficulty.h"

void HandleDifficultyProcess(enum GAME_STATE *game_state, enum GAME_DIFFICULTY *game_difficulty, Texture2D game_icon_texture, Texture2D back_image_texture) {
  // Define the difficulty modes
  const char *difficulty_mode_text[] = { "Easy",
                                         "Medium",
                                         "Hard"};

  // Count how many difficulty modes are there
  int difficulty_mode_count = sizeof(difficulty_mode_text) / sizeof(difficulty_mode_text[0]);

  // Store each mode in a clickable area as a Rectangle
  Rectangle difficulty_mode_buttons[difficulty_mode_count];

  static int selected_button = -1;

  // Layout settings
  int start_y = 200, // Where the first mode will be drawn vertically
      spacing = 60,  // Vertical spacing between modes
      button_width = 250, // Fixed width for all buttons
      button_height = 50; // Fixed height for all buttons

  // Precompute button rectangles for each mode
  for (int i = 0; i < difficulty_mode_count; i++) {
    int button_x = (WINDOW_WIDTH / 2) - (button_width / 2),
        button_y = start_y + (i * spacing);

    // Save button rectangle for drawing and input detection
    difficulty_mode_buttons[i] = (Rectangle) { button_x, button_y, button_width, button_height};
  }

  Rectangle back_button = { 10, 10, back_image_texture.width, back_image_texture.height};

  // Process the input for the difficulty mode menu
  ProcessDifficultyInput(game_state, game_difficulty, difficulty_mode_buttons, difficulty_mode_count, &selected_button, back_button);

  // Render the difficulty mode menu with the appropriate elements
  RenderDifficultyPage(game_icon_texture, back_image_texture, difficulty_mode_buttons, difficulty_mode_text, difficulty_mode_count, selected_button);
}

void HandleDifficultyAction(enum GAME_STATE *game_state, enum GAME_DIFFICULTY *game_difficulty, int selected_button) {
  switch (selected_button) {
    case 0: // "Easy"
      *game_difficulty = EASY;
      ChangeGameState(game_state, PLAYING);
      break;

    case 1: // "Medium"
      *game_difficulty = MEDIUM;
      ChangeGameState(game_state, PLAYING);
      break;

    case 2: // "Hard"
      *game_difficulty = HARD;
      ChangeGameState(game_state, PLAYING);
      break;
  }
}
