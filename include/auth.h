#pragma once

#include "./process.h"
#include "./player.h"
#include "./render.h"
#include "./config.h"

// Function used to handle the sign up process
void HandleSignUpProcess(struct Player *player, enum GAME_STATE *game_state, Texture2D game_icon_texture, Texture2D required_image_texture);

// Function used to handle the log in process
void HandleLogInProcess(struct Player *player, enum GAME_STATE *game_state, Texture2D game_icon_texture, Texture2D required_image_texture);