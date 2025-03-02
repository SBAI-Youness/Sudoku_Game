#pragma once

#include "./input.h"
#include "./player.h"
#include "./draw.h"
#include "./config.h"

// Function used to handle the sign up process
void HandleSignUpProcess(struct Player *player, Texture2D game_icon_texture, enum GAME_STATE *game_state);

// Function used to handle the log in process
void HandleLogInProcess(struct Player *player, Texture2D game_icon_texture, enum GAME_STATE *game_state);