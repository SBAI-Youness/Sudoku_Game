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

enum GAME_STATE {
  SIGN_UP,
  LOG_IN,
  MAIN_MENU,
  MODE_MENU,
  PLAYING
};

struct InputBox {
  Rectangle box;  // Input field dimension
  bool isActive; // Flag to track if the input field is active or not
  bool isEmpty; // Flag to track if the input field was filled or not (in a way false means don't show the required input field image)
};

// Function used to initialize the window and game settings
extern void InitializeWindowAndSettings();

// Function used to change the game state to a desired one
extern void ChangeGameState(enum GAME_STATE *game_state, enum GAME_STATE new_state);

// Function used to close the window and clean up resources
extern void CloseWindowAndCleanUp();