#include "../include/tutorial.h"

void HandleTutorialProcess(enum GAME_STATE *game_state, Texture2D game_icon_texture, Texture2D back_image_texture) {
  Rectangle back_button = { 10, 10, back_image_texture.width, back_image_texture.height};

  ProcessTutorialInput(game_state, back_button);

  RenderTutorialPage(game_icon_texture, back_image_texture);
}
