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

void CloseWindowAndCleanUp() {
  // Close the window and OpenGL context
  CloseWindow();
}