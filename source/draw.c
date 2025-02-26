#include "../include/draw.h"

Texture2D LoadResizedTexture(const char *file_name, int new_width, int new_height) {
  // Load the image from the file
  Image image = LoadImage(file_name);

  // Resize the image to the new width and height
  ImageResize(&image, new_width, new_height);

  // Convert the resized image into a texture (for rendering in raylib)
  Texture2D texture = LoadTextureFromImage(image);

  // Free the memory occupied by the original image data (since it's no longer needed)
  UnloadImage(image);

  // Return the texture object to be used for rendering
  return texture;
}

void RenderSignUpPage(Texture2D game_icon_texture, enum GAME_STATE *game_state) {
  // Draw game icon in the top right corner
  DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

  // Input field dimensions
  Rectangle name_box = { (WINDOW_WIDTH / 2) - 200, 200, 400, 50},
            password_box = { (WINDOW_WIDTH / 2) - 200, 300, 400, 50};

  // Title
  DrawText("Sign Up", (WINDOW_WIDTH / 2) - 80, 100, 40, DARKGRAY);

  // Input field labels
  DrawText("Player Name:", name_box.x, name_box.y - 30, 20, BLACK);
  DrawText("Password:", password_box.x, password_box.y - 30, 20, BLACK);

  // Draw input fields
  DrawRectangleRec(name_box, LIGHTGRAY);
  DrawRectangleRec(password_box, LIGHTGRAY);

  // Placeholder text inside fields
  //TODO: Yeah, Yeah, I know. I want the labels for each input, but at the moment, let things be simple as much as possible. Yay!
  //* DrawText("Enter your name...", name_box.x + 10, name_box.y + 15, 18, GRAY);
  //* DrawText("Enter your password...", password_box.x + 10, password_box.y + 15, 18, GRAY);

  // Log in prompt
  const char *text = "Already have an account? Log in";
  int text_width = MeasureText(text, 20), // Get text width dynamically
      text_x_position = (WINDOW_WIDTH / 2) + (name_box.width / 2) - text_width,
      text_y_position = password_box.y + password_box.height + 40;

  // Define the clickable area
  Rectangle log_in_box = { text_x_position, text_y_position, text_width, 20};

  // Change color on hover
  Color text_color = (CheckCollisionPointRec(GetMousePosition(), log_in_box) == true)? RED: BLUE;

  // Draw the log in prompt
  DrawText(text, text_x_position, text_y_position, 20, text_color);

  // Check for click
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(GetMousePosition(), log_in_box) == true)
    ChangeGameState(game_state, LOG_IN);
}

void RenderLogInPage(Texture2D game_icon_texture, enum GAME_STATE *game_state) {
  // Draw game icon in the top right corner
  DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

  // Input field dimensions
  Rectangle name_box = { (WINDOW_WIDTH / 2) - 200, 200, 400, 50},
            password_box = { (WINDOW_WIDTH / 2) - 200, 300, 400, 50};

  // Title
  DrawText("Log In", (WINDOW_WIDTH / 2) - 80, 100, 40, DARKGRAY);

  // Input field labels
  DrawText("Player Name:", name_box.x, name_box.y - 30, 20, BLACK);
  DrawText("Password:", password_box.x, password_box.y - 30, 20, BLACK);

  // Draw input fields
  DrawRectangleRec(name_box, LIGHTGRAY);
  DrawRectangleRec(password_box, LIGHTGRAY);

  //TODO: Yeah, Yeah, I know. I want the labels for each input, but at the moment, let things be simple as much as possible. Yay!
  // Placeholder text inside fields
  //* DrawText("Enter your name...", name_box.x + 10, name_box.y + 15, 18, GRAY);
  //* DrawText("Enter your password...", password_box.x + 10, password_box.y + 15, 18, GRAY);

  // Sign up prompt
  const char *text = "Don't have an account? Sign up";
  int text_width = MeasureText(text, 20), // Get text width dynamically
      text_x_position = (WINDOW_WIDTH / 2) + (name_box.width / 2) - text_width,
      text_y_position = password_box.y + password_box.height + 40;

  // Define the clickable area
  Rectangle sign_up_box = { text_x_position, text_y_position, text_width, 20};

  // Change color on hover
  Color text_color = (CheckCollisionPointRec(GetMousePosition(), sign_up_box) == true)? RED: BLUE;

  // Draw the sign up prompt
  DrawText(text, text_x_position, text_y_position, 20, text_color);

  // Check for click
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(GetMousePosition(), sign_up_box) == true)
    ChangeGameState(game_state, SIGN_UP);
}