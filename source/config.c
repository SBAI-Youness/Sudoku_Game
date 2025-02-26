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

void CloseWindowAndCleanUp(void) {
  // Close the window and OpenGL context
  CloseWindow();
}