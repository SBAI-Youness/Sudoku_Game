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

void RenderPlayingPage(struct Player *player, enum GAME_DIFFICULTY game_difficulty, struct Cell grid[GRID_SIZE][GRID_SIZE], int selected_row, int selected_column, bool last_move_correct, bool is_paused, double paused_at) {
  // Show difficulty at top-left
  const char *diff_str = "";
  switch (game_difficulty) {
    case EASY:
      diff_str = "Difficulty: Easy";
      break;
    case MEDIUM:
      diff_str = "Difficulty: Medium";
      break;
    case HARD:
      diff_str = "Difficulty: Hard";
      break;
  }
  DrawText(diff_str, 10, 10, 20, DARKGRAY);

  // Calculate top-left offset so the grid is centered on the screen
  int grid_x = (WINDOW_WIDTH - (GRID_SIZE * CELL_SIZE)) / 2,
      grid_y = (WINDOW_HEIGHT - (GRID_SIZE * CELL_SIZE)) / 2;

  double elapsed = 0.0;

  if (is_paused == true && paused_at > 0.0) {
    elapsed = paused_at - player->start_time;
  }
  else {
    elapsed = GetTime() - player->start_time;
  }

  int minutes = (int) (elapsed / 60);
  int seconds = (int) elapsed % 60;

  char timer_text[16];
  snprintf(timer_text, sizeof(timer_text), "%02d:%02d", minutes, seconds);

  int ttw = MeasureText(timer_text, 20);
  DrawText(timer_text, WINDOW_WIDTH - ttw - 10, 10, 20, DARKBLUE);

  // Draw grid cells
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      // Define the rectangle for this cell
      Rectangle cell = {grid_x + (col * CELL_SIZE), grid_y + (row * CELL_SIZE), CELL_SIZE, CELL_SIZE};

      // Highlight selected cell
      if (row == selected_row && col == selected_column) {
        DrawRectangleRec(cell, (Color){200, 230, 255, 255}); // soft blue highlight
      } else if (grid[row][col].is_fixed) {
        DrawRectangleRec(cell, (Color){220, 220, 220, 255}); // light gray for fixed cells
      } else {
        DrawRectangleRec(cell, RAYWHITE); // white for editable cells
      }

      // Draw the border of the cell
      DrawRectangleLinesEx(cell, 1, BLACK);

      // If the cell contains a number, draw it
      if (grid[row][col].value != 0) {
        char num[2];
        snprintf(num, 2, "%d", grid[row][col].value);

        // Measure text width to center number horizontally
        int tw = MeasureText(num, 20);

        Color text_color;
        if (grid[row][col].is_fixed == true) {
          text_color = BLACK;
        }
        else if (grid[row][col].is_correct == false) {
          text_color = RED;  // wrong move stays red
        }
        else {
          text_color = BLUE; // correct player input
        }

        // If player entered this number and it’s wrong, show RED
        if (!grid[row][col].is_fixed && row == selected_row && col == selected_column && !last_move_correct) {
          text_color = RED;
        }

        // Draw the number centered in the cell
        DrawText(num, cell.x + ((CELL_SIZE - tw) / 2), cell.y + ((CELL_SIZE - 20) / 2), 20, text_color);
      }
    }
  }

  // Bold lines for 3x3 sub-grids
  for (int i = 0; i <= GRID_SIZE; i++) {
    // every 3rd line is thicker
    int thickness = (i % SUB_GRID_SIZE == 0)? 3 : 1;

    // Vertical
    DrawLineEx((Vector2) {grid_x + (i * CELL_SIZE), grid_y}, (Vector2) {grid_x + (i * CELL_SIZE), grid_y + (GRID_SIZE * CELL_SIZE)}, thickness, BLACK);

    // Horizontal
    DrawLineEx((Vector2) {grid_x, grid_y + (i * CELL_SIZE)}, (Vector2) {grid_x + (GRID_SIZE * CELL_SIZE), grid_y + (i * CELL_SIZE)}, thickness, BLACK);
  }

  // Message if current selection is wrong
  if (selected_row != -1 && selected_column != -1) {
    struct Cell *cell = &grid[selected_row][selected_column];
    if (!cell->is_fixed && cell->value != 0 && !cell->is_correct) {
      DrawText("Incorrect move!", grid_x, grid_y + (GRID_SIZE * CELL_SIZE) + 10, 20, RED);
    }
  }

  // Show mistakes at top center
  char mistakes_text[32];
  snprintf(mistakes_text, sizeof(mistakes_text), "Mistakes: %d/3", player->mistakes);
  int mtw = MeasureText(mistakes_text, 20);
  DrawText(mistakes_text,
      grid_x + (GRID_SIZE * CELL_SIZE - mtw) / 2, // centered over grid
      grid_y - 26,                                // just above grid
      20,
      RED);
}

Rectangle RenderPauseButton(Texture2D pause_image_texture) {
  int x = (WINDOW_WIDTH - pause_image_texture.width) / 2;
  int y = 10;
  DrawTexture(pause_image_texture, x, y, WHITE);
  Rectangle pause_button = { x, y, pause_image_texture.width, pause_image_texture.height };
  return pause_button;
}

void RenderPauseOverlayPage(Rectangle *resume_button, Rectangle *restart_button, Rectangle *main_menu_button, int *selected_button) {
  DrawRectangle(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, (Color){0, 0, 0, 160});

  const char *title = "Paused";
  int title_font = 40;
  int title_w = MeasureText(title, title_font);
  DrawText(title, (WINDOW_WIDTH - title_w) / 2, WINDOW_HEIGHT / 4, title_font, RAYWHITE);

  int button_w = 220;
  int button_h = 48;
  int spacing = 18;
  int start_y = WINDOW_HEIGHT / 2 - (button_h * 3 + spacing * 2) / 2;
  int x = (WINDOW_WIDTH - button_w) / 2;

  *resume_button = (Rectangle){ x, start_y, button_w, button_h };
  *restart_button = (Rectangle){ x, start_y + button_h + spacing, button_w, button_h };
  *main_menu_button = (Rectangle){ x, start_y + (button_h + spacing) * 2, button_w, button_h };

  Rectangle buttons[3] = {*resume_button, *restart_button, *main_menu_button};
  const char *labels[3] = {"Resume", "Restart", "Main Menu"};

  Vector2 mouse = GetMousePosition();
  for (int i = 0; i < 3; i++) {
    Color bg = LIGHTGRAY;
    if (CheckCollisionPointRec(mouse, buttons[i])) {
      bg = GRAY;
      if (selected_button != NULL) *selected_button = i;
    }
    DrawRectangleRec(buttons[i], bg);
    DrawRectangleLines((int)buttons[i].x, (int)buttons[i].y, (int)buttons[i].width, (int)buttons[i].height, DARKGRAY);

    int tw = MeasureText(labels[i], 20);
    DrawText(labels[i], buttons[i].x + (buttons[i].width - tw) / 2, buttons[i].y + (buttons[i].height - 20) / 2, 20, BLACK);
  }
}

void RenderResultPage(bool did_win, double elapsed_seconds, enum GAME_DIFFICULTY game_difficulty, struct Cell final_grid[GRID_SIZE][GRID_SIZE], struct Cell (*solution_grid)[GRID_SIZE], Rectangle *play_again_button, Rectangle *main_menu_button) {
  const char *title = did_win ? "You Won!" : "You Lost";
  Color title_color = did_win ? GREEN : RED;

  int title_font = 40;
  int title_w = MeasureText(title, title_font);
  DrawText(title, (WINDOW_WIDTH - title_w) / 2, 40, title_font, title_color);

  // Difficulty text
  const char *diff_str = "";
  switch (game_difficulty) {
    case EASY: diff_str = "Difficulty: Easy"; break;
    case MEDIUM: diff_str = "Difficulty: Medium"; break;
    case HARD: diff_str = "Difficulty: Hard"; break;
  }
  DrawText(diff_str, 20, 100, 20, DARKGRAY);

  // Time text
  int minutes = (int)(elapsed_seconds / 60);
  int seconds = (int)elapsed_seconds % 60;
  char time_text[32];
  snprintf(time_text, sizeof(time_text), "Time: %02d:%02d", minutes, seconds);
  int ttw = MeasureText(time_text, 20);
  DrawText(time_text, WINDOW_WIDTH - ttw - 20, 100, 20, DARKBLUE);

  // Compute grid positions (side-by-side if lost; single if win)
  int grid_pixel = GRID_SIZE * CELL_SIZE;
  int grid_y = 150;

  if (did_win == true) {
    int grid_x = (WINDOW_WIDTH - grid_pixel) / 2;

    // Draw final grid
    for (int row = 0; row < GRID_SIZE; row++) {
      for (int col = 0; col < GRID_SIZE; col++) {
        Rectangle cell = (Rectangle){ grid_x + col * CELL_SIZE, grid_y + row * CELL_SIZE, CELL_SIZE, CELL_SIZE };
        DrawRectangleRec(cell, RAYWHITE);
        DrawRectangleLinesEx(cell, 1, BLACK);

        if (final_grid[row][col].value != 0) {
          char num[2];
          snprintf(num, 2, "%d", final_grid[row][col].value);
          int tw = MeasureText(num, 20);
          Color color = final_grid[row][col].is_fixed ? BLACK : BLUE;
          DrawText(num, cell.x + (CELL_SIZE - tw) / 2, cell.y + (CELL_SIZE - 20) / 2, 20, color);
        }
      }
    }

    // Bold subgrid lines
    for (int i = 0; i <= GRID_SIZE; i++) {
      int thickness = (i % SUB_GRID_SIZE == 0) ? 3 : 1;
      DrawLineEx((Vector2){grid_x + i * CELL_SIZE, grid_y}, (Vector2){grid_x + i * CELL_SIZE, grid_y + grid_pixel}, thickness, BLACK);
      DrawLineEx((Vector2){grid_x, grid_y + i * CELL_SIZE}, (Vector2){grid_x + grid_pixel, grid_y + i * CELL_SIZE}, thickness, BLACK);
    }
  } else {
    // Lost: show only the solution grid centered
    bool has_solution = (solution_grid != NULL);

    if (!has_solution) {
      const char *msg = "Solution not available";
      int mw = MeasureText(msg, 20);
      DrawText(msg, (WINDOW_WIDTH - mw) / 2, grid_y + grid_pixel / 2 - 10, 20, RED);
    } else {
      int grid_x = (WINDOW_WIDTH - grid_pixel) / 2;

      const char *label = "Solution";
      int lw = MeasureText(label, 18);
      DrawText(label, grid_x + (grid_pixel - lw) / 2, grid_y - 26, 18, DARKGRAY);

      for (int row = 0; row < GRID_SIZE; row++) {
        for (int col = 0; col < GRID_SIZE; col++) {
          Rectangle cell = (Rectangle){ grid_x + col * CELL_SIZE, grid_y + row * CELL_SIZE, CELL_SIZE, CELL_SIZE };
          DrawRectangleRec(cell, RAYWHITE);
          DrawRectangleLinesEx(cell, 1, BLACK);

          if (solution_grid[row][col].value != 0) {
            char num[2]; snprintf(num, 2, "%d", solution_grid[row][col].value);
            int tw = MeasureText(num, 20);
            // Highlight cells that differ from player's entries in GREEN; otherwise BLACK
            Color scolor = (final_grid[row][col].value != solution_grid[row][col].value) ? GREEN : BLACK;
            DrawText(num, cell.x + (CELL_SIZE - tw) / 2, cell.y + (CELL_SIZE - 20) / 2, 20, scolor);
          }
        }
      }

      // Bold subgrid lines
      for (int i = 0; i <= GRID_SIZE; i++) {
        int thickness = (i % SUB_GRID_SIZE == 0) ? 3 : 1;
        DrawLineEx((Vector2){grid_x + i * CELL_SIZE, grid_y}, (Vector2){grid_x + i * CELL_SIZE, grid_y + grid_pixel}, thickness, BLACK);
        DrawLineEx((Vector2){grid_x, grid_y + i * CELL_SIZE}, (Vector2){grid_x + grid_pixel, grid_y + i * CELL_SIZE}, thickness, BLACK);
      }
    }
  }

  // Buttons aligned at bottom center
  int button_w = 200;
  int button_h = 48;
  int spacing = 20;
  int total = button_w * 2 + spacing;
  int x = (WINDOW_WIDTH - total) / 2;
  int y = WINDOW_HEIGHT - button_h - 30;

  *play_again_button = (Rectangle){ x, y, button_w, button_h };
  *main_menu_button = (Rectangle){ x + button_w + spacing, y, button_w, button_h };

  Vector2 mouse = GetMousePosition();
  Rectangle buttons[2] = { *play_again_button, *main_menu_button };
  const char *labels[2] = { "Play Again", "Main Menu" };

  for (int i = 0; i < 2; i++) {
    bool hover = CheckCollisionPointRec(mouse, buttons[i]);
    Color bg = hover ? (Color){ 173, 216, 230, 255 } : BLUE;
    DrawRectangleRec(buttons[i], bg);
    DrawRectangleLines((int)buttons[i].x, (int)buttons[i].y, (int)buttons[i].width, (int)buttons[i].height, DARKGRAY);
    int tw = MeasureText(labels[i], 20);
    DrawText(labels[i], buttons[i].x + (buttons[i].width - tw) / 2, buttons[i].y + (buttons[i].height - 20) / 2, 20, BLACK);
  }
}
