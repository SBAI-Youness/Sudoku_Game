#include <stdlib.h>
#include "../include/config.h"
#include "../include/raylib.h"

int main() {
  // Initialize the window with the specified width, height, and game name
  InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, GAME_NAME);

  // Set the game's target frame rate to 60 frames per second
  SetTargetFPS(60);

  // Main game loop: runs until the window is closed
  while (WindowShouldClose() == false) {
    // Begin drawing the frame
    BeginDrawing();

    // Clear the screen with a blue background color (RGB: 46, 88, 255, 255)
    ClearBackground((Color){ 46, 88, 255, 255});

    // End the drawing of the current frame
    EndDrawing();
  }

  // Close the window and clean up resources
  CloseWindow();

  return EXIT_SUCCESS;
}