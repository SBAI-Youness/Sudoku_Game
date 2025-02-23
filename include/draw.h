#pragma once

#include "./config.h"

// Function used to load an image from file, resize it to new dimensions, and return it as a texture
Texture2D LoadResizedTexture(const char *file_name, int new_width, int new_height);