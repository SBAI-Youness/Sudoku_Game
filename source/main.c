#include <stdlib.h>
#include <stdbool.h>
#include "../include/config.h"
#include "../include/draw.h"

int main() {
  InitializeWindowAndSettings();

  // Load an image texture
  Texture2D game_icon_texture = LoadResizedTexture("../assets/icons/game_icon.png", WINDOW_WIDTH / 8, WINDOW_HEIGHT / 8);

  // Main game loop: runs until the window is closed
  while (WindowShouldClose() == false) {
    // Begin drawing the frame
    BeginDrawing();

    // Clear the screen with a white background color
    ClearBackground(WHITE);

    DrawTexture(game_icon_texture, GAME_ICON_X_POSITION, GAME_ICON_Y_POSITION, WHITE);

    // End the drawing of the current frame
    EndDrawing();
  }

  // Unload the game icon texture
  UnloadTexture(game_icon_texture);

  CloseWindowAndCleanUp();

  return EXIT_SUCCESS;
}