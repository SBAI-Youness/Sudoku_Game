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

void RenderSignUpPage(struct Player *player, Texture2D game_icon_texture, Rectangle name_box, Rectangle password_box, Rectangle log_in_box, const char *log_in_text, Vector2 log_in_text_position) {
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

  // Draw the current player name and password inside their respective input fields
  DrawText(player->name, (int) (name_box.x + 10), (int) (name_box.y + 10), 20, BLACK);
  DrawText(player->password, (int) (password_box.x + 10), (int) (password_box.y + 10), 20, BLACK);

  // Draw the player's name or placeholder
  if (strlen(player->name) > 0)
    DrawText(player->name, (int) (name_box.x + 10), (int) (name_box.y + 10), 20, BLACK);
  else
    DrawText("Enter your name", (int) (name_box.x + 10), (int) (name_box.y + 10), 20, GRAY);

  // Draw the player's password or placeholder
  if (strlen(player->password) > 0)
    DrawText(player->password, (int) (password_box.x + 10), (int) (password_box.y + 10), 20, BLACK);
  else
    DrawText("Enter your password", (int) (password_box.x + 10), (int) (password_box.y + 10), 20, GRAY);

  // Change color on hover
  Color text_color = (CheckCollisionPointRec(GetMousePosition(), log_in_box) == true)? RED: BLUE;

  // Draw the log in prompt
  DrawText(log_in_text, (int) log_in_text_position.x, (int) log_in_text_position.y, 20, text_color);
}

void RenderLogInPage(struct Player *player, Texture2D game_icon_texture, Rectangle name_box, Rectangle password_box, Rectangle sign_up_box, const char *sign_up_text, Vector2 sign_up_text_position) {
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

  // Draw the current player name and password inside their respective input fields
  DrawText(player->name, (int) (name_box.x + 10), (int) (name_box.y + 10), 20, BLACK);
  DrawText(player->password, (int) (password_box.x + 10), (int) (password_box.y + 10), 20, BLACK);

  // Draw the player's name or placeholder
  if (strlen(player->name) > 0)
    DrawText(player->name, (int) (name_box.x + 10), (int) (name_box.y + 10), 20, BLACK);
  else
    DrawText("Enter your name", (int) (name_box.x + 10), (int) (name_box.y + 10), 20, GRAY);

  // Draw the player's password or placeholder
  if (strlen(player->password) > 0)
    DrawText(player->password, (int) (password_box.x + 10), (int) (password_box.y + 10), 20, BLACK);
  else
    DrawText("Enter your password", (int) (password_box.x + 10), (int) (password_box.y + 10), 20, GRAY);

  // Change color on hover
  Color text_color = (CheckCollisionPointRec(GetMousePosition(), sign_up_box) == true)? RED: BLUE;

  // Draw the sign up prompt
  DrawText(sign_up_text, (int) (int) sign_up_text_position.x, (int) (int) sign_up_text_position.y, 20, text_color);
}