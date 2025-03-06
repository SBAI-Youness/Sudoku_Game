#pragma once

#include "./player.h"
#include "./raylib.h"

// Function used to process the player input while signing up
void ProcessSignUpInput(struct Player *player, enum GAME_STATE *game_state, Rectangle name_box, bool *isNameBoxActive, Rectangle password_box, bool *isPasswordBoxActive, Rectangle log_in_box, Rectangle sign_up_button, bool *isNameEmpty, bool *isPasswordEmpty);

// Function used to process the player input while loging in
void ProcessLogInInput(struct Player *player, enum GAME_STATE *game_state, Rectangle name_box, bool *isNameBoxActive, Rectangle password_box, bool *isPasswordBoxActive, Rectangle sign_up_box, Rectangle log_in_button, bool *isNameEmpty, bool *isPasswordEmpty);