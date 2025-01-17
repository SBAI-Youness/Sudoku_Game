#pragma once

#include "./config.h"

#define GAME_NAME "Sudoku Game"

// Forreground text colors
#define RESET       "\033[0m" // Reset the text color to teh default
#define RED         "\033[31m" // For the game over
#define GREEN       "\033[32m" // For the congratulations
#define YELLOW      "\033[1;33m" // For the click to continue message
#define ORANGE      "\033[38;5;208m" // For the warning messages
#define BLUE        "\033[34m" // For the game name
#define LIGHT_BLUE  "\033[38;2;173;216;230m" // For the added cells
#define DARK_GREEN  "\033[38;2;0;102;51m" // For the menus

// Text styles
#define BOLD        "\033[1m" // For bold texts
#define UNDERLINE   "\033[4m" // For underlined texts

// Display delay in seconds
#define DISPLAY_DELAY 4

// Function used to display the game name underlined in blue and bold
extern void display_game_name();

// Function used to display the main menu and get the user's choice
extern void display_main_menu(uint8_t *main_menu_choice);

// Function used to display the game modes (Easy, Medium, Hard) and get the user's choice
extern void display_game_mode_menu(uint8_t *game_mode_choice);

// Function used to display the rules of the game
extern void display_how_to_play();

// Function used to display an error message
extern void display_error_message(const char *message);

// Function used to display an invalid choice message
extern void display_invalid_choice();

// Function used to display a message indicating that the input is invalid
extern void display_invalid_input();

// Function used to display a message indicating that the game is over and the player has won
extern void display_congratulations(double time_spent);

// Function used to display a message indicating that the game is over
extern void display_game_over();