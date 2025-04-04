#pragma once

#include "./config.h"
#include "./player.h"
#include "./process.h"

// Function used to load an image from file, resize it to new dimensions, and return it as a texture
extern Texture2D LoadResizedTexture(const char *file_name, int new_width, int new_height);

// Function used to render the sign up page
extern void RenderSignUpPage(struct Player *player, Texture2D game_icon_texture, Texture2D required_image_texture, struct InputBox name_box, bool isNameUnique, struct InputBox password_box, Rectangle log_in_box, Vector2 log_in_text_position, const char *log_in_text, Rectangle sign_up_button);

// Function used to render the log in page
extern void RenderLogInPage(struct Player *player, Texture2D game_icon_texture, Texture2D required_image_texture, struct InputBox name_box, struct InputBox password_box, bool isAuthenticated, Rectangle sign_up_box, Vector2 sign_up_text_position, const char *sign_up_text, Rectangle log_in_button);