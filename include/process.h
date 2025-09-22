#pragma once

#include "./player.h"
#include "./auth.h"
#include "./config.h"
#include "./raylib.h"
#include "./menu.h"
#include "./difficulty.h"
#include "./play.h"

// Function used to process the player input while signing up
extern void ProcessSignUpInput(struct Player *player, enum GAME_STATE *game_state, struct InputBox *name_box, bool *isNameUnique, struct InputBox *password_box, Rectangle log_in_box, Rectangle sign_up_button);

// Function used to process the player input while loging in
extern void ProcessLogInInput(struct Player *player, enum GAME_STATE *game_state, struct InputBox *name_box, struct InputBox *password_box, bool *isAuthenticated, Rectangle sign_up_box, Rectangle log_in_button);

// Function used to process the player input while being in the game menu
extern void ProcessGameMenuInput(struct Player *player, enum GAME_STATE *game_state, Rectangle menu_buttons[], int menu_count, int *selected_button);

// Function used to process the player input while being in the tutorial screen
extern void ProcessTutorialInput(enum GAME_STATE *game_state, Rectangle back_button);

// Function used to process the player input while being prompted to choose the game difficulty
extern void ProcessDifficultyInput(enum GAME_STATE *game_state, enum GAME_DIFFICULTY *game_difficulty, Rectangle difficulty_mode_buttons[], int difficulty_mode_count, int *selected_button, Rectangle back_button);

// Function used to process the player input inside the game
extern void ProcessPlayingInput(struct Player *player, struct Cell grid[GRID_SIZE][GRID_SIZE], int *selected_row, int *selected_column, bool *last_move_correct, bool *is_paused, Rectangle pause_button);

extern void ProcessPauseOverlayInput(enum GAME_STATE *game_state, bool *is_paused, bool *restart_requested, Rectangle resume_button, Rectangle restart_button, Rectangle main_menu_button);

// Function used to process input on the result page
extern void ProcessResultInput(Rectangle play_again_button, Rectangle main_menu_button, bool *play_again_clicked, bool *main_menu_clicked);
