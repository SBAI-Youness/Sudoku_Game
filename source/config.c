#include "../include/config.h"

void InitializeWindowAndSettings() {
  // Initialize the window with the specified width, height, and game name
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);

  // Set the game's target frame rate to 60 frames per second
  SetTargetFPS(60);
}

void ChangeGameState(enum GAME_STATE *game_state, enum GAME_STATE new_state) {
  // Safety check to prevent dereferencing a null pointer
  if (game_state == NULL)
    return;

  // Update the game state to the new state
  (*game_state) = new_state;
}

void ResetInputBoxes(struct InputBox *name_box, struct InputBox *password_box) {
  name_box->isActive = false;
  password_box->isActive = false;

  name_box->validation.isValid = true;
  password_box->validation.isValid = true;

  name_box->validation.error_message = NULL;
  password_box->validation.error_message = NULL;
}

void DrawSpinner(Vector2 center, float radius, int trail_count, float circle_size, Color color, float time) {
  for (int i = 0; i < trail_count; i++) {
    // Spread dots evenly around the circle
    float angle = time + ((2 * PI) / trail_count) * i;

    float x = center.x + cosf(angle) * radius;
    float y = center.y + sinf(angle) * radius;

    // Fade based on position in the circle (smooth gradient)
    unsigned char alpha = (unsigned char) (80 + 175.0f * ((float) i / trail_count));

    Color faded = (Color) {color.r, color.g, color.b, alpha};

    DrawCircle((int) x, (int) y, circle_size, faded);
  }
}

void SaveSudokuGrid(struct Cell grid[GRID_SIZE][GRID_SIZE], const char *file_path) {
  // Open the file in write mode ("w" = overwrite if exists)
  FILE *file = fopen(file_path, "w");

  // Check if fopen failed or not
  if (file == NULL) {
    return;
  }

  // Loop through every cell in the Sudoku grid
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int column = 0; column < GRID_SIZE; column++) {
      // Write the cell value followed by a space
      fprintf(file, "%d ", grid[row][column].value);
    }

    // After each row, insert a newline
    fprintf(file, "\n");
  }

  // Close the file to free resources and flush the buffer
  fclose(file);
}

void CloseWindowAndCleanUp() {
  // Close the window and OpenGL context
  CloseWindow();
}
