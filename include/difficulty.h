#pragma once

#include "../include/config.h"
#include "../include/process.h"
#include "../include/render.h"

extern void HandleDifficultyProcess(enum GAME_STATE *game_state, enum GAME_DIFFICULTY *game_difficulty, Texture2D game_icon_texture, Texture2D back_image_texture);

extern void HandleDifficultyAction(enum GAME_STATE *game_state, enum GAME_DIFFICULTY *game_difficulty, int selected_button);
