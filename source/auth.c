#include "../include/auth.h"

void HandleSignUpProcess(struct Player *player, enum GAME_STATE *game_state, Texture2D game_icon_texture, Texture2D required_image_texture) {
  // Flags to track which input field is currently active
  static bool isNameBoxActive = false,
              isPasswordBoxActive = false;

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

  // Define the "Sign Up" button position and size
  Rectangle sign_up_button = { (WINDOW_WIDTH / 2) - 75, log_in_box.y + log_in_box.height + 20, 150, 50};

  // Flags to track if the input fields where filled or not (in a way false means don't show the required input field image)
  static bool isNameEmpty = false,
              isPasswordEmpty = false;

  // Flag to track if the name is usique or not
  static bool isNameUnique = true;

  // Process the input for the sign up form (name and password)
  ProcessSignUpInput(player, game_state, name_box, &isNameBoxActive, password_box, &isPasswordBoxActive, log_in_box, sign_up_button, &isNameEmpty, &isPasswordEmpty, &isNameUnique);

  // Render the sign up page with the appropriate elements (input boxes, text, icon)
  RenderSignUpPage(player, game_icon_texture, required_image_texture, name_box, isNameBoxActive, isNameEmpty, isNameUnique, password_box, isPasswordBoxActive, isPasswordEmpty, log_in_box, (Vector2) { text_x_position, text_y_position}, text, sign_up_button);
}

void HandleLogInProcess(struct Player *player, enum GAME_STATE *game_state, Texture2D game_icon_texture, Texture2D required_image_texture) {
  // Flags to track which input field is currently active
  static bool isNameBoxActive = false,
              isPasswordBoxActive = false;

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

  // Define the "Log In" button position and size
  Rectangle log_in_button = { (WINDOW_WIDTH / 2) - 75, sign_up_box.y + sign_up_box.height + 20, 150, 50};

  // Flags to track if the input fields where filled or not (in a way false means don't show the required input field image)
  static bool isNameEmpty = false,
              isPasswordEmpty = false;

  // Process the input for the log in form (name and password)
  ProcessLogInInput(player, game_state, name_box, &isNameBoxActive, password_box, &isPasswordBoxActive, sign_up_box, log_in_button, &isNameEmpty, &isPasswordEmpty);

  // Render the log in page with the appropriate elements (input boxes, text, icon)
  RenderLogInPage(player, game_icon_texture, required_image_texture, name_box, isNameBoxActive, isNameEmpty, password_box, isPasswordBoxActive, isPasswordEmpty, sign_up_box, (Vector2) { text_x_position, text_y_position}, text, log_in_button);
}