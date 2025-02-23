#pragma once

#include "../include/raylib.h"

#define GAME_NAME "Sudoku Game"

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define GAME_ICON_X_POSITION (WINDOW_WIDTH - game_icon_texture.width - 10)
#define GAME_ICON_Y_POSITION 10

// Function used to initialize the window and game settings
void InitializeWindowAndSettings();

// Function used to close the window and clean up resources
void CloseWindowAndCleanUp();