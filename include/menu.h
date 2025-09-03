#pragma once

#include "./config.h"
#include "./player.h"
#include "./process.h"
#include "./render.h"

// Function used to handle the player input while being in the main menu
extern void HandleGameMenuProcess(struct Player *player, enum GAME_STATE *game_state, Texture2D game_icon_texture);

// Function used to handle the button actions
extern void HandleGameMenuAction(struct Player *player, enum GAME_STATE *game_state, int selected_button);
