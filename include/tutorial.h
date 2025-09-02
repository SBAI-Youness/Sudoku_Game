#pragma once

#include "./config.h"
#include "./process.h"
#include "./render.h"

// Function used to handle the tutorial process
extern void HandleTutorialProcess(enum GAME_STATE *game_state, Texture2D game_icon_texture, Texture2D back_image_texture);
