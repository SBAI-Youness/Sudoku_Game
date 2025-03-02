#pragma once

#include "./player.h"
#include "./raylib.h"

// Function used to process the player input while signing up
void ProcessSignUpInput(struct Player *player, Rectangle name_box, Rectangle password_box, Rectangle log_in_box, bool *isNameBoxActive, bool *isPasswordBoxActive, enum GAME_STATE *game_state);

// Function used to process the player input while loging in
void ProcessLogInInput(struct Player *player, Rectangle name_box, Rectangle password_box, Rectangle sign_up_box, bool *isNameBoxActive, bool *isPasswordBoxActive, enum GAME_STATE *game_state);