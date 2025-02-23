#include "../include/draw.h"

Texture2D LoadResizedTexture(const char *file_name, int new_width, int new_height) {
  // Load the image from the file
  Image image = LoadImage(file_name);

  // Resize the image to the new width and height
  ImageResize(&image, new_width, new_height);

  // Convert the resized image into a texture (for rendering in raylib)
  Texture2D texture = LoadTextureFromImage(image);

  // Free the memory occupied by the original image data (since it's no longer needed)
  UnloadImage(image);

  // Return the texture object to be used for rendering
  return texture;
}