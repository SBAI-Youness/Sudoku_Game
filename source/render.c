#include "../include/render.h"

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

void RenderSignUpPage(struct Player *player, Texture2D game_icon_texture, Rectangle name_box, bool isNameBoxActive, Rectangle password_box, bool isPasswordBoxActive, Rectangle log_in_box, Vector2 log_in_text_position, const char *log_in_text) {
  // Draw game icon in the top right corner
  DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

  // Title
  DrawText("Sign Up", (WINDOW_WIDTH / 2) - 80, 100, 40, DARKGRAY);

  // Input field labels
  DrawText("Player Name:", (int) name_box.x, (int) name_box.y - 30, 20, BLACK);
  DrawText("Password:", (int) password_box.x, (int) password_box.y - 30, 20, BLACK);

  // Draw input fields
  DrawRectangleRec(name_box, LIGHTGRAY);
  DrawRectangleRec(password_box, LIGHTGRAY);

  // Get the current time in seconds
  float current_time = GetTime();

  // Create a blinking effect: alternate visibility every 0.5 seconds
  bool show_cursor = ((int) (current_time * 2) % 2) == 0;

  // Text input padding
  int padding_x = 10,
      padding_y = 10;

  // Thicker and taller cursor
  int cursor_width = 3,
      cursor_height = 24;

  // Draw the player's name or placeholder
  if (strlen(player->name) > 0)
    DrawText(player->name, (int) (name_box.x + 10), (int) (name_box.y + 10), 20, BLACK);
  else
    DrawText("Enter your name", (int) (name_box.x + 10), (int) (name_box.y + 10), 20, GRAY);

  // Draw thick cursor in name box if active
  if (isNameBoxActive == true && show_cursor) {
    int name_text_width = MeasureText(player->name, 20);
    DrawRectangle((int) (name_box.x + padding_x + name_text_width), (int) (name_box.y + padding_y), cursor_width, cursor_height, BLACK);
  }

  // Draw the player's password or placeholder
  if (strlen(player->password) > 0)
    DrawText(player->password, (int) (password_box.x + 10), (int) (password_box.y + 10), 20, BLACK);
  else
    DrawText("Enter your password", (int) (password_box.x + 10), (int) (password_box.y + 10), 20, GRAY);

  // Draw cursor in password box if active
  if (isPasswordBoxActive  == true && show_cursor == true) {
    int pass_text_width = MeasureText(player->password, 20);
    DrawRectangle((int) (password_box.x + padding_x + pass_text_width), (int) (password_box.y + padding_y), cursor_width, cursor_height, BLACK);
  }

  // Change color on hover
  Color text_color = (CheckCollisionPointRec(GetMousePosition(), log_in_box) == true)? RED: BLUE;

  // Draw the log in prompt
  DrawText(log_in_text, (int) log_in_text_position.x, (int) log_in_text_position.y, 20, text_color);
}

void RenderLogInPage(struct Player *player, Texture2D game_icon_texture, Rectangle name_box, bool isNameBoxActive, Rectangle password_box, bool isPasswordBoxActive, Rectangle sign_up_box, Vector2 sign_up_text_position, const char *sign_up_text) {
  // Draw game icon in the top right corner
  DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

  // Title
  DrawText("Log In", (WINDOW_WIDTH / 2) - 80, 100, 40, DARKGRAY);

  // Input field labels
  DrawText("Player Name:", (int) name_box.x, (int) name_box.y - 30, 20, BLACK);
  DrawText("Password:", (int) password_box.x, (int) password_box.y - 30, 20, BLACK);

  // Draw input fields
  DrawRectangleRec(name_box, LIGHTGRAY);
  DrawRectangleRec(password_box, LIGHTGRAY);

  // Get the current time in seconds
  float current_time = GetTime();

  // Create a blinking effect: alternate visibility every 0.5 seconds
  bool show_cursor = ((int) (current_time * 2) % 2) == 0;

  // Text input padding
  int padding_x = 10,
      padding_y = 10;

  // Thicker and taller cursor
  int cursor_width = 3,
      cursor_height = 24;

  // Draw the player's name or placeholder
  if (strlen(player->name) > 0)
    DrawText(player->name, (int) (name_box.x + 10), (int) (name_box.y + 10), 20, BLACK);
  else
    DrawText("Enter your name", (int) (name_box.x + 10), (int) (name_box.y + 10), 20, GRAY);

  // Draw thick cursor in name box if active
  if (isNameBoxActive == true && show_cursor) {
    int name_text_width = MeasureText(player->name, 20);
    DrawRectangle((int) (name_box.x + padding_x + name_text_width), (int) (name_box.y + padding_y), cursor_width, cursor_height, BLACK);
  }

  // Draw the player's password or placeholder
  if (strlen(player->password) > 0)
    DrawText(player->password, (int) (password_box.x + 10), (int) (password_box.y + 10), 20, BLACK);
  else
    DrawText("Enter your password", (int) (password_box.x + 10), (int) (password_box.y + 10), 20, GRAY);

  // Draw cursor in password box if active
  if (isPasswordBoxActive  == true && show_cursor == true) {
    int pass_text_width = MeasureText(player->password, 20);
    DrawRectangle((int) (password_box.x + padding_x + pass_text_width), (int) (password_box.y + padding_y), cursor_width, cursor_height, BLACK);
  }

  // Change color on hover
  Color text_color = (CheckCollisionPointRec(GetMousePosition(), sign_up_box) == true)? RED: BLUE;

  // Draw the sign up prompt
  DrawText(sign_up_text, (int) sign_up_text_position.x, (int) sign_up_text_position.y, 20, text_color);
}