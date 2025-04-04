#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "./raylib.h"

#define GAME_NAME "Sudoku Game"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define GAME_ICON_X_POSITION (WINDOW_WIDTH - game_icon_texture.width - 10)
#define GAME_ICON_Y_POSITION 10

#define STR_HELPER(x) #x
#define STR(x) STR_HELPER(x)

// Authorized special characters
#define ALLOWED_SPECIAL_CHARACTERS "!@#$%^&*()_+-=[]{}|;:,.<>?"

enum GAME_STATE {
  SIGN_UP,
  LOG_IN,
  MAIN_MENU,
  MODE_MENU,
  PLAYING
};

// Structure to store the results of the validation
struct ValidationResult {
  bool isValid;
  const char *error_message;
};

struct InputBox {
  Rectangle box;  // Input field dimension
  bool isActive; // Flag to track if the input field is active or not
  struct ValidationResult validation; // Structure to track if the input field is valid or not, with an error message
};

// Function used to initialize the window and game settings
extern void InitializeWindowAndSettings();

// Function used to change the game state to a desired one
extern void ChangeGameState(enum GAME_STATE *game_state, enum GAME_STATE new_state);

// Function used to reset the input boxes while signing up or logging in
extern void ResetInputBoxes(struct InputBox *name_box, struct InputBox *password_box);

// Function used to close the window and clean up resources
extern void CloseWindowAndCleanUp();