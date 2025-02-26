#include <stdlib.h>
#include <stdbool.h>
#include "../include/config.h"
#include "../include/draw.h"

int main() {
  InitializeWindowAndSettings();

  // Define the initial game state as SIGN_UP
  enum GAME_STATE game_state = SIGN_UP;

  // Load an image texture
  Texture2D game_icon_texture = LoadResizedTexture("../assets/icons/game_icon.png", WINDOW_WIDTH / 8, WINDOW_HEIGHT / 8);

  // Main game loop: runs until the window is closed
  while (WindowShouldClose() == false) {
    // Process

    // Update

    // Begin drawing the frame
    BeginDrawing();

    // Clear the screen with a white background color
    ClearBackground(WHITE);

    switch (game_state) {
      case SIGN_UP:
        RenderSignUpPage(game_icon_texture, &game_state);
        break;

      case LOG_IN:
        RenderLogInPage(game_icon_texture, &game_state);
        break;

      case MAIN_MENU:
        break;
      case MODE_MENU:
        break;
      case PLAYING:
        break;

      default:
        break;
    }

    // End the drawing of the current frame
    EndDrawing();
  }

  // Unload the game icon texture
  UnloadTexture(game_icon_texture);

  CloseWindowAndCleanUp();

  return EXIT_SUCCESS;
}