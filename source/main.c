#include "../include/config.h"
#include "../include/render.h"
#include "../include/player.h"
#include "../include/process.h"
#include "../include/auth.h"

int main() {
  InitializeWindowAndSettings();

  // Define the initial game state as SIGN_UP
  enum GAME_STATE game_state = SIGN_UP;

  // Load an image texture
  Texture2D game_icon_texture = LoadResizedTexture("../assets/icons/game_icon.png", WINDOW_WIDTH / 8, WINDOW_HEIGHT / 8),
            required_image_texture = LoadResizedTexture("../assets/images/required.png", 28, 28);

  // Create a player pointer (NULL initially)
  struct Player *player = NULL;

  // Main game loop: runs until the window is closed
  while (WindowShouldClose() == false) {
    // Begin drawing the frame
    BeginDrawing();

    // Clear the screen with a white background color
    ClearBackground(WHITE);

    switch (game_state) {
      case SIGN_UP:
        if (player == NULL)
          player = CreatePlayer(); // Create player when signing up

        if (player == NULL) {
          TraceLog(LOG_ERROR, "Failed to create a player structure!\n");
          return EXIT_FAILURE;
        }

        HandleSignUpProcess(player, &game_state, game_icon_texture, required_image_texture);

        break;

      case LOG_IN:
        if (player == NULL)
          player = CreatePlayer(); // Create player when logging in

        if (player == NULL) {
          TraceLog(LOG_ERROR, "Failed to create a player structure!\n");
          return EXIT_FAILURE;
        }

        HandleLogInProcess(player, &game_state, game_icon_texture, required_image_texture);

        break;

      case MAIN_MENU:
        break;
      case MODE_MENU:
        break;
      case PLAYING:
        break;
    }

    // End the drawing of the current frame
    EndDrawing();
  }

  // Cleanup: Free player before exiting
  if (player != NULL)
    player->FreePlayer(player);

  // Unload textures
  UnloadTexture(required_image_texture);
  UnloadTexture(game_icon_texture);

  CloseWindowAndCleanUp();

  return EXIT_SUCCESS;
} 