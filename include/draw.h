#pragma once

#include "./config.h"

// Function used to load an image from file, resize it to new dimensions, and return it as a texture
Texture2D LoadResizedTexture(const char *file_name, int new_width, int new_height);

// Function used to render the sign up page
void RenderSignUpPage(Texture2D game_icon_texture, enum GAME_STATE *game_state);

// Function used to render the log in page
void RenderLogInPage(Texture2D game_icon_texture, enum GAME_STATE *game_state);