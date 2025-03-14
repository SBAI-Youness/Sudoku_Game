#pragma once

#include "./player.h"
#include "./auth.h"
#include "./config.h"
#include "./raylib.h"

// Function used to process the player input while signing up
extern void ProcessSignUpInput(struct Player *player, enum GAME_STATE *game_state, struct InputBox *name_box, bool *isNameUnique, struct InputBox *password_box, Rectangle log_in_box, Rectangle sign_up_button);

// Function used to process the player input while loging in
extern void ProcessLogInInput(struct Player *player, enum GAME_STATE *game_state, struct InputBox *name_box, struct InputBox *password_box, bool *isAuthenticated, Rectangle sign_up_box, Rectangle log_in_button);