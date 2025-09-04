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

void RenderSignUpPage(struct Player *player, Texture2D game_icon_texture, Texture2D required_image_texture, struct InputBox name_box, bool isNameUnique, struct InputBox password_box, Rectangle log_in_box, Vector2 log_in_text_position, const char *log_in_text, Rectangle sign_up_button) {
  // Draw game icon in the top right corner
  DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

  // Title
  DrawText("Sign Up", (WINDOW_WIDTH / 2) - 80, 100, 40, DARKGRAY);

  // Input field labels
  DrawText("Player Name:", (int) name_box.box.x, (int) name_box.box.y - 30, 20, BLACK);
  DrawText("Password:", (int) password_box.box.x, (int) password_box.box.y - 30, 20, BLACK);

  // Draw input fields
  DrawRectangleRec(name_box.box, LIGHTGRAY);
  DrawRectangleRec(password_box.box, LIGHTGRAY);

  // Draw border around the active input field
  if (name_box.isActive == true)
    DrawRectangleLines((int) name_box.box.x, (int) name_box.box.y, (int) name_box.box.width, (int) name_box.box.height, BLACK);
  else if (password_box.isActive == true)
    DrawRectangleLines((int) password_box.box.x, (int) password_box.box.y, (int) password_box.box.width, (int) password_box.box.height, BLACK);

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
    DrawText(player->name, (int) (name_box.box.x + 10), (int) (name_box.box.y + 10), 20, BLACK);
  else
    DrawText("Enter your name", (int) (name_box.box.x + 10), (int) (name_box.box.y + 10), 20, GRAY);

  // Draw thick cursor in name box if active
  if (name_box.isActive == true && show_cursor == true) {
    int name_text_width = MeasureText(player->name, 20);
    DrawRectangle((int) (name_box.box.x + padding_x + name_text_width), (int) (name_box.box.y + padding_y), cursor_width, cursor_height, BLACK);
  }

  // Draw error message if name is taken
  if (isNameUnique == false && name_box.isActive == false)
    DrawText("Name already taken!", (int) ((WINDOW_WIDTH / 2) + (name_box.box.width / 2) - 210), (int) (name_box.box.y + name_box.box.height + 2), 20, RED);

  // Draw the player's password or placeholder
  if (strlen(player->password) > 0)
    DrawText(player->password, (int) (password_box.box.x + 10), (int) (password_box.box.y + 10), 20, BLACK);
  else
    DrawText("Enter your password", (int) (password_box.box.x + 10), (int) (password_box.box.y + 10), 20, GRAY);

  // Draw cursor in password box if active
  if (password_box.isActive == true && show_cursor == true) {
    int pass_text_width = MeasureText(player->password, 20);
    DrawRectangle((int) (password_box.box.x + padding_x + pass_text_width), (int) (password_box.box.y + padding_y), cursor_width, cursor_height, BLACK);
  }

  // Draw error messages if fields are invalid
  if (name_box.validation.isValid == false && name_box.isActive == false) {
    if (strlen(player->name) == 0)
      DrawTexture(required_image_texture, (int) (name_box.box.x + name_box.box.width - 33), (int) (name_box.box.y + 10), WHITE);
    else
      DrawText(name_box.validation.error_message, (int) ((WINDOW_WIDTH / 2) + (name_box.box.width / 2) - 350), (int) (name_box.box.y + name_box.box.height + 2), 20, RED);
  }

  if (password_box.validation.isValid == false && password_box.isActive == false) {
    if (strlen(player->password) == 0)
      DrawTexture(required_image_texture, (int) (password_box.box.x + password_box.box.width - 33), (int) (password_box.box.y + 10), WHITE);
    else
      DrawText(password_box.validation.error_message, (int) ((WINDOW_WIDTH / 2) + (password_box.box.width / 2) - 350), (int) (password_box.box.y + password_box.box.height + 2), 20, RED);
  }

  // Change color on hover
  Color text_color = (CheckCollisionPointRec(GetMousePosition(), log_in_box) == true)? RED: BLUE;

  // Draw the log in prompt
  DrawText(log_in_text, (int) log_in_text_position.x, (int) log_in_text_position.y, 20, text_color);

  // Draw the "Sign Up" button
  Color button_color = (CheckCollisionPointRec(GetMousePosition(), sign_up_button) == true)? DARKGRAY: GRAY;
  DrawRectangleRec(sign_up_button, button_color);

  // Center the text inside the button
  int text_width = MeasureText("Sign Up", 20),  // Measure the width of the "Sign Up" text
      text_x_position = sign_up_button.x + (sign_up_button.width / 2) - (text_width / 2), // Center horizontally
      text_y_position = sign_up_button.y + (sign_up_button.height / 2) - 10; // Center vertically

  DrawText("Sign Up", text_x_position, text_y_position, 20, WHITE);
}

void RenderLogInPage(struct Player *player, Texture2D game_icon_texture, Texture2D required_image_texture, struct InputBox name_box, struct InputBox password_box, bool isAuthenticated, Rectangle sign_up_box, Vector2 sign_up_text_position, const char *sign_up_text, Rectangle log_in_button) {
  // Draw game icon in the top right corner
  DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

  // Title
  DrawText("Log In", (WINDOW_WIDTH / 2) - 80, 100, 40, DARKGRAY);

  // Input field labels
  DrawText("Player Name:", (int) name_box.box.x, (int) name_box.box.y - 30, 20, BLACK);
  DrawText("Password:", (int) password_box.box.x, (int) password_box.box.y - 30, 20, BLACK);

  // Draw input fields
  DrawRectangleRec(name_box.box, LIGHTGRAY);
  DrawRectangleRec(password_box.box, LIGHTGRAY);

  // Draw border around the active input field
  if (name_box.isActive == true)
    DrawRectangleLines((int) name_box.box.x, (int) name_box.box.y, (int) name_box.box.width, (int) name_box.box.height, BLACK);
  else if (password_box.isActive == true)
    DrawRectangleLines((int) password_box.box.x, (int) password_box.box.y, (int) password_box.box.width, (int) password_box.box.height, BLACK);

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
    DrawText(player->name, (int) (name_box.box.x + 10), (int) (name_box.box.y + 10), 20, BLACK);
  else
    DrawText("Enter your name", (int) (name_box.box.x + 10), (int) (name_box.box.y + 10), 20, GRAY);

  // Draw thick cursor in name box if active
  if (name_box.isActive == true && show_cursor == true) {
    int name_text_width = MeasureText(player->name, 20);
    DrawRectangle((int) (name_box.box.x + padding_x + name_text_width), (int) (name_box.box.y + padding_y), cursor_width, cursor_height, BLACK);
  }

  // Draw the player's password or placeholder
  if (strlen(player->password) > 0)
    DrawText(player->password, (int) (password_box.box.x + 10), (int) (password_box.box.y + 10), 20, BLACK);
  else
    DrawText("Enter your password", (int) (password_box.box.x + 10), (int) (password_box.box.y + 10), 20, GRAY);

  // Draw cursor in password box if active
  if (password_box.isActive == true && show_cursor == true) {
    int pass_text_width = MeasureText(player->password, 20);
    DrawRectangle((int) (password_box.box.x + padding_x + pass_text_width), (int) (password_box.box.y + padding_y), cursor_width, cursor_height, BLACK);
  }

  // Draw error messages if fields are invalid
  if (name_box.validation.isValid == false && name_box.isActive == false) {
    if (strlen(player->name) == 0)
      DrawTexture(required_image_texture, (int) (name_box.box.x + name_box.box.width - 33), (int) (name_box.box.y + 10), WHITE);
    else
      DrawText(name_box.validation.error_message, (int) ((WINDOW_WIDTH / 2) + (name_box.box.width / 2) - 350), (int) (name_box.box.y + name_box.box.height + 2), 20, RED);
  }

  if (password_box.validation.isValid == false && password_box.isActive == false) {
    if (strlen(player->password) == 0)
      DrawTexture(required_image_texture, (int) (password_box.box.x + password_box.box.width - 33), (int) (password_box.box.y + 10), WHITE);
    else
      DrawText(password_box.validation.error_message, (int) ((WINDOW_WIDTH / 2) + (password_box.box.width / 2) - 350), (int) (password_box.box.y + password_box.box.height + 2), 20, RED);
  }

  if (isAuthenticated == false && password_box.isActive == false)
    DrawText("Invalid credentials. Try again.", (int) ((WINDOW_WIDTH / 2) + (password_box.box.width / 2) - 314), (int) (password_box.box.y + password_box.box.height + 2), 20, RED);

  // Change color on hover
  Color text_color = (CheckCollisionPointRec(GetMousePosition(), sign_up_box) == true)? RED: BLUE;

  // Draw the sign up prompt
  DrawText(sign_up_text, (int) sign_up_text_position.x, (int) sign_up_text_position.y, 20, text_color);

  // Draw the "Log In" button
  Color button_color = (CheckCollisionPointRec(GetMousePosition(), log_in_button) == true)? DARKGRAY: GRAY;
  DrawRectangleRec(log_in_button, button_color);

  // Center the text inside the button
  int text_width = MeasureText("Log In", 20),  // Measure the width of the "Log In" text
      text_x_position = log_in_button.x + (log_in_button.width / 2) - (text_width / 2), // Center horizontally
      text_y_position = log_in_button.y + (log_in_button.height / 2) - 10; // Center vertically

  DrawText("Log In", text_x_position, text_y_position, 20, WHITE);
}

void RenderGameMenuPage(Texture2D game_icon_texture, Rectangle menu_buttons[], const char *game_menu_text[], int menu_count, int selected_button) {
  // Draw game icon in the top right corner
  DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

  // Title: Sudoku Game (centered at the top)
  const char *title = "Sudoku Game";
  int title_font_size = 40;
  int title_width = MeasureText(title, title_font_size);
  DrawText(title, (WINDOW_WIDTH - title_width) / 2, 100, title_font_size, DARKBLUE);

  // Get the current mouse position
  Vector2 mouse_position = GetMousePosition();

  for (int i = 0; i < menu_count; i++) {
    // Check if the button is hovered
    bool hover = CheckCollisionPointRec(mouse_position, menu_buttons[i]);

    // Draw button background
    DrawRectangleRec(menu_buttons[i], (hover == true || selected_button == i)? (Color) { 173, 216, 230, 255} : BLUE);

    // Center text inside button
    int text_width = MeasureText(game_menu_text[i], 20),
        text_x = menu_buttons[i].x + (menu_buttons[i].width / 2) - (text_width / 2),
        text_y = menu_buttons[i].y + (menu_buttons[i].height / 2) - (20 / 2);

    DrawText(game_menu_text[i], text_x, text_y, 20, BLACK);
  }
}

void RenderTutorialPage(Texture2D game_icon_texture, Texture2D back_image_texture) {
  // Draw game icon in the top right corner
  DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

  // Draw the back sign image
  DrawTexture(back_image_texture, 10, 10, WHITE);

  // Title settings
  int title_font = 30;
  const char *title = "How To Play Sudoku";
  int title_width = MeasureText(title, title_font);
  DrawText(title, (WINDOW_WIDTH - title_width) / 2, 100, title_font, DARKBLUE);

  // Text lines
  const char *lines[] = {
      "- Fill the 9x9 grid so each row, column,",
      "  and 3x3 box contains the numbers 1-9.",
      "- Each number can only appear once per row,",
      "  column, and box.",
      "- Click a cell, then enter a number (1-9).",
      "- Use BACKSPACE or 0 to erase a number.",
      "- Complete the board correctly to win!"
  };
  int line_count = sizeof(lines) / sizeof(lines[0]);

  // Text rendering settings
  int font_size = 20;
  int line_spacing = 40;
  int y = 180; // starting Y under title

  // Loop through each line of instructions and draw them centered
  for (int i = 0; i < line_count; i++) {
    int text_width = MeasureText(lines[i], font_size);
    DrawText(lines[i], (WINDOW_WIDTH - text_width) / 2, y, font_size, BLACK);
    y += line_spacing; // Move down for the next line
  }
}

void RenderDifficultyPage(Texture2D game_icon_texture, Texture2D back_image_texture, Rectangle difficulty_mode_buttons[], const char *difficulty_mode_text[], int difficulty_mode_count, int selected_button) {
  // Draw game icon in the top right corner
  DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

  // Draw the back sign image
  DrawTexture(back_image_texture, 10, 10, WHITE);

  // Title: Choose Difficulty (centered at the top)
  const char *title = "Choose Difficulty";
  int title_font_size = 30;
  int title_width = MeasureText(title, title_font_size);
  DrawText(title, (WINDOW_WIDTH - title_width) / 2, 100, title_font_size, DARKBLUE);

  // Get the current mouse position
  Vector2 mouse_position = GetMousePosition();

  for (int i = 0; i < difficulty_mode_count; i++) {
    // Check if the button is hovered
    bool hover = CheckCollisionPointRec(mouse_position, difficulty_mode_buttons[i]);

    // Draw button background
    DrawRectangleRec(difficulty_mode_buttons[i], (hover == true || selected_button == i)? (Color) { 173, 216, 230, 255} : BLUE);

    // Center text inside button
    int text_width = MeasureText(difficulty_mode_text[i], 20),
        text_x = difficulty_mode_buttons[i].x + (difficulty_mode_buttons[i].width / 2) - (text_width / 2),
        text_y = difficulty_mode_buttons[i].y + (difficulty_mode_buttons[i].height / 2) - (20 / 2);

    DrawText(difficulty_mode_text[i], text_x, text_y, 20, BLACK);
  }
}
