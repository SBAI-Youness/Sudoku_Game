#pragma once

#include "./config.h"

#define GAME_NAME "Sudoku Game"

// Function used to display the game name
extern void display_game_name();

// Function used to display the main menu and get the user's choice
extern void display_main_menu(uint8_t *main_menu_choice);

// Function used to display the game modes (Easy, Medium, Hard) and get the user's choice
extern void display_game_mode_menu(uint8_t *game_mode_choice);

// Function used to display the rules of the game
extern void display_how_to_play();

// Function used to display an invalid choice message
extern void display_invalid_choice();

// Function used to display a message indicating that the input is invalid
extern void display_invalid_input();

// Function used to display a message indicating that the game is over
extern void display_game_over();