#include "../include/auth.h"

void HandleSignUpProcess(struct Player *player, Texture2D game_icon_texture, enum GAME_STATE *game_state) {
  // Flags to track which input field is currently active
  static bool isNameActive = false,
       isPasswordActive = false;

  // Input field dimensions
  Rectangle name_box = { (WINDOW_WIDTH / 2) - 200, 200, 400, 50},
            password_box = { (WINDOW_WIDTH / 2) - 200, 300, 400, 50};

  // Text to prompt the player to log in if they already have an account
  const char *text = "Already have an account? Log in";
  int text_width = MeasureText(text, 20), // Get text width dynamically
      text_x_position = (WINDOW_WIDTH / 2) + (name_box.width / 2) - text_width,
      text_y_position = password_box.y + password_box.height + 40;

  // Define the clickable area for the "Log in" text
  Rectangle log_in_box = { text_x_position, text_y_position, text_width, 20};

  // Process the input for the sign up form (name and password)
  ProcessSignUpInput(player, name_box, password_box, log_in_box, &isNameActive, &isPasswordActive, game_state);

  // Render the sign up page with the appropriate elements (input boxes, text, icon)
  RenderSignUpPage(player, game_icon_texture, name_box, password_box, isNameActive, isPasswordActive, log_in_box, text, (Vector2) { text_x_position, text_y_position});
}

void HandleLogInProcess(struct Player *player, Texture2D game_icon_texture, enum GAME_STATE *game_state) {
  // Flags to track which input field is currently active
  static bool isNameActive = false,
       isPasswordActive = false;

  // Input field dimensions
  Rectangle name_box = { (WINDOW_WIDTH / 2) - 200, 200, 400, 50},
            password_box = { (WINDOW_WIDTH / 2) - 200, 300, 400, 50};

  // Text to prompt the player to sign up if they don't have an account
  const char *text = "Don't have an account? Sign up";
  int text_width = MeasureText(text, 20), // Get text width dynamically
      text_x_position = (WINDOW_WIDTH / 2) + (name_box.width / 2) - text_width,
      text_y_position = password_box.y + password_box.height + 40;

  // Define the clickable area for the "Sign Up" text
  Rectangle sign_up_box = { text_x_position, text_y_position, text_width, 20};

  // Process the input for the log in form (name and password)
  ProcessLogInInput(player, name_box, password_box, sign_up_box, &isNameActive, &isPasswordActive, game_state);

  // Render the log in page with the appropriate elements (input boxes, text, icon)
  RenderLogInPage(player, game_icon_texture, name_box, password_box, isNameActive, isPasswordActive, sign_up_box, text, (Vector2) { text_x_position, text_y_position});
}