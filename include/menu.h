#pragma once

#include "./player.h"
#include "./process.h"
#include "./render.h"

extern void HandleGameMenuProcess(struct Player *player, enum GAME_STATE *game_state, Texture2D game_icon_texture);
