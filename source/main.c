#include "../include/config.h"
#include "../include/render.h"
#include "../include/player.h"
#include "../include/process.h"
#include "../include/auth.h"
#include "../include/menu.h"
#include "../include/difficulty.h"
#include "../include/tutorial.h"
#include "../include/play.h"
#include "../include/result.h"

int main() {
  InitializeWindowAndSettings();

  // Define the initial game state as SIGN_UP
  enum GAME_STATE game_state = SIGN_UP;

  // Define the initial game difficulty as EASY
  enum GAME_DIFFICULTY game_difficulty = EASY;

  // Spinner timer
  float spinnerTime = 0.0f;
  float spinnerElapsed = 0.0f;
  const float spinnerDuration = 1.0f;

  // Load an image texture
  Texture2D game_icon_texture = LoadResizedTexture("../assets/icons/game_icon.png", WINDOW_WIDTH / 8, WINDOW_HEIGHT / 8),
            required_image_texture = LoadResizedTexture("../assets/images/required.png", 28, 28),
            back_image_texture = LoadResizedTexture("../assets/images/back.png", 28, 28),
            pause_image_texture = LoadResizedTexture("../assets/images/pause.png", 28, 28);

  // Create a player pointer (NULL initially)
  struct Player *player = NULL;

  // Main game loop: runs until the window is closed
  while (WindowShouldClose() == false) {
    float dt = GetFrameTime();

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

        if (game_state == MAIN_MENU) {
          ChangeGameState(&game_state, LOADING);

          spinnerTime = 0;
          spinnerElapsed = 0;
        }

        break;

      case LOG_IN:
        if (player == NULL)
          player = CreatePlayer(); // Create player when logging in

        if (player == NULL) {
          TraceLog(LOG_ERROR, "Failed to create a player structure!\n");
          return EXIT_FAILURE;
        }

        HandleLogInProcess(player, &game_state, game_icon_texture, required_image_texture);

        if (game_state == MAIN_MENU) {
          ChangeGameState(&game_state, LOADING);

          spinnerTime = 0;
          spinnerElapsed = 0;
        }

        break;

      case MAIN_MENU:
        HandleGameMenuProcess(player, &game_state, game_icon_texture);
        break;

      case MODE_MENU:
        HandleDifficultyProcess(&game_state, &game_difficulty, game_icon_texture, back_image_texture);
        break;

      case TUTORIAL:
        HandleTutorialProcess(&game_state, game_icon_texture, back_image_texture);
        break;

      case PLAYING:
        HandlePlayingProcess(player, &game_state, &game_difficulty, pause_image_texture);
        break;

      case LOADING:
        spinnerElapsed += dt;
        spinnerTime += dt * 2.0f; // spin speed

        DrawSpinner((Vector2) {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2}, 18.0f, 28, 7.0f, SKYBLUE, spinnerTime);

        if (spinnerElapsed >= spinnerDuration) {
          ChangeGameState(&game_state, MAIN_MENU);
        }

        break;

      case RESULT:
        HandleResultProcess(&game_state, &game_difficulty);
        break;

      case EXIT:
        goto clean_up;
        break;
    }

    // End the drawing of the current frame
    EndDrawing();
  }

  // Cleanup resources
  clean_up:

  // Cleanup: Free player before exiting
  if (player != NULL)
    player->FreePlayer(player);

  // Unload textures
  UnloadTexture(required_image_texture);
  UnloadTexture(game_icon_texture);
  UnloadTexture(back_image_texture);
  UnloadTexture(pause_image_texture);

  CloseWindowAndCleanUp();

  return EXIT_SUCCESS;
}
