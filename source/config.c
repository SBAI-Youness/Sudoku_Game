#include "../include/config.h"

void InitializeWindowAndSettings() {
  // Initialize the window with the specified width, height, and game name
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);

  // Set the game's target frame rate to 60 frames per second
  SetTargetFPS(60);
}

void CloseWindowAndCleanUp(void) {
  // Close the window
  CloseWindow();
}