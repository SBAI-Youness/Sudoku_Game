#pragma once

#include "./config.h"
#include "./player.h"
#include "./process.h"

// Function used to load an image from file, resize it to new dimensions, and return it as a texture
Texture2D LoadResizedTexture(const char *file_name, int new_width, int new_height);

// Function used to render the sign up page
void RenderSignUpPage(struct Player *player, Texture2D game_icon_texture, Rectangle name_box, bool isNameBoxActive, Rectangle password_box, bool isPasswordBoxActive, Rectangle log_in_box, Vector2 log_in_text_position, const char *log_in_text, Rectangle sign_up_button);

// Function used to render the log in page
void RenderLogInPage(struct Player *player, Texture2D game_icon_texture, Rectangle name_box, bool isNameBoxActive, Rectangle password_box, bool isPasswordBoxActive, Rectangle sign_up_box, Vector2 sign_up_text_position, const char *sign_up_text, Rectangle log_in_button);