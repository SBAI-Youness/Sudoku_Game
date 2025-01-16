#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#include "./ui.h"
#include "./sudoku.h"

// Forreground text colors
#define RESET       "\033[0m"
#define RED         "\033[31m" // For the game over
#define GREEN       "\033[32m" // For the congratulations
#define YELLOW      "\033[1;33m" // For the click to continue message
#define ORANGE      "\033[38;5;208m" // For the warning messages
#define BLUE        "\033[34m" // For the game name
#define LIGHT_BLUE  "\033[38;2;173;216;230m" // For the added cells
#define DARK_GREEN  "\033[38;2;0;102;51m" // For the menus

// Text styles
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"

#define INVALID_DELAY 4
#define GAME_OVER_AND_CONGRATULATIONS_DELAY 5

// Function used to clear the input buffer until a newline character or an end of file is encountered
extern void clear_input_buffer();