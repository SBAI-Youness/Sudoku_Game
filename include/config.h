#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>
#include <math.h>
#include <windows.h> // Even though I hate Windows (Microsoft), I have to use it for this project

#include "./ui.h"
#include "./sudoku.h"

#define RESET       "\033[0m"
#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[1;33m"
#define ORANGE      "\033[38;5;208m"
#define DARK_GREEN  "\033[38;2;0;102;51m"
#define BLUE        "\033[34m"
#define CYAN        "\033[1;36m"
#define BROWN       "\033[38;2;139;69;19m"

// Text styles
#define BOLD        "\033[1m"
#define UNDERLINE   "\033[4m"

// Function used to clear the input buffer
extern void clear_input_buffer();