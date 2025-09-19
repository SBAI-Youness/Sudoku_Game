#include "../include/result.h"
#include "../include/render.h"
#include "../include/process.h"

void HandleResultProcess(enum GAME_STATE *game_state, enum GAME_DIFFICULTY *game_difficulty) {
  static struct Cell solution_grid[GRID_SIZE][GRID_SIZE];
  bool has_solution = LoadSolutionGrid(solution_grid, SOLUTION_FILE);

  Rectangle play_again_button, main_menu_button;
  RenderResultPage(g_result.did_win, g_result.elapsed_seconds, g_result.difficulty, g_result.final_grid, has_solution ? solution_grid : NULL, &play_again_button, &main_menu_button);

  bool play_again_clicked = false, main_menu_clicked = false;
  ProcessResultInput(game_state, play_again_button, main_menu_button, &play_again_clicked, &main_menu_clicked);

  if (play_again_clicked == true) {
    *game_difficulty = g_result.difficulty;
    ChangeGameState(game_state, PLAYING);
  }
  else if (main_menu_clicked == true) {
    ChangeGameState(game_state, MAIN_MENU);
  }
} 