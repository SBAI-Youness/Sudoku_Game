#include "../include/play.h"
#include <stdio.h>

void HandlePlayingProcess(struct Player *player, enum GAME_STATE *game_state, enum GAME_DIFFICULTY *game_difficulty, Texture2D pause_image_texture) {
  static struct Cell grid[GRID_SIZE][GRID_SIZE];
  static bool initialized = false,
              last_move_correct = true;
  static int selected_row = -1,
             selected_column = -1;
  static bool is_paused = false;
  static double paused_at = 0.0;

  if (initialized == false) {
    // seed random once
    srand((unsigned int)time(NULL));

    bool loaded = false;
    if (player->resume_requested == true) {
      loaded = LoadGameState(player, game_difficulty, grid);
    }

    if (loaded == false) {
      GenerateSudokuGrid(grid, *game_difficulty);
      player->mistakes = 0;
      player->start_time = GetTime();
    }

    initialized = true;
    is_paused = false;
    paused_at = 0.0;
  }

  Rectangle pause_button = RenderPauseButton(pause_image_texture);

  if (is_paused == true) {
    if (paused_at == 0.0) {
      paused_at = GetTime();
    }

    RenderPlayingPage(player, *game_difficulty, grid, selected_row, selected_column, last_move_correct, is_paused, paused_at);

    // Overlay with buttons
    Rectangle resume_button, restart_button, main_menu_button;
    int hovered = -1;
    RenderPauseOverlayPage(&resume_button, &restart_button, &main_menu_button, &hovered);

    bool restart_requested = false;
    ProcessPauseOverlayInput(game_state, &is_paused, &restart_requested, resume_button, restart_button, main_menu_button);

    if (is_paused == false && paused_at != 0.0) {
      double paused_duration = GetTime() - paused_at;
      player->start_time += paused_duration;
      paused_at = 0.0;
    }

    if (*game_state != PLAYING) {
      initialized = false;
      selected_row = selected_column = -1;
      is_paused = false;
      paused_at = 0.0;

      return;
    }

    if (restart_requested == true) {
      GenerateSudokuGrid(grid, *game_difficulty);
      player->mistakes = 0;
      player->start_time = GetTime();
      last_move_correct = true;
      selected_row = selected_column = -1;
      is_paused = false;
      paused_at = 0.0;
    }

    return;
  }

  ProcessPlayingInput(player, grid, &selected_row, &selected_column, &last_move_correct, &is_paused, pause_button);

  if (is_paused == false) {
    RenderPlayingPage(player, *game_difficulty, grid, selected_row, selected_column, last_move_correct, is_paused, paused_at);

    // Autosave
    SaveGameState(player, *game_difficulty, grid);

    if (player->mistakes >= 3) {
      DeleteGameState(player);
      // Populate result context for LOSS
      g_result.did_win = false;
      g_result.difficulty = *game_difficulty;
      double elapsed = GetTime() - player->start_time;
      g_result.elapsed_seconds = elapsed;
      for (int r = 0; r < GRID_SIZE; r++)
        for (int c = 0; c < GRID_SIZE; c++)
          g_result.final_grid[r][c] = grid[r][c];
      ChangeGameState(game_state, RESULT);

      // Reset local state for next entry
      initialized = false;
      selected_row = selected_column = -1;
      is_paused = false;
      paused_at = 0.0;
      return;
    }

    if (is_puzzle_solved(grid) == true) {
      DeleteGameState(player);
      // Populate result context for WIN
      g_result.did_win = true;
      g_result.difficulty = *game_difficulty;
      double elapsed = GetTime() - player->start_time;
      g_result.elapsed_seconds = elapsed;
      for (int r = 0; r < GRID_SIZE; r++)
        for (int c = 0; c < GRID_SIZE; c++)
          g_result.final_grid[r][c] = grid[r][c];
      ChangeGameState(game_state, RESULT);

      // Reset local state for next entry
      initialized = false;
      selected_row = selected_column = -1;
      is_paused = false;
      paused_at = 0.0;
    }
  }
}

void GenerateSudokuGrid(struct Cell grid[GRID_SIZE][GRID_SIZE], enum GAME_DIFFICULTY game_difficulty) {
  // Reset the grid to a clean state before generating a new puzzle
  for (int r = 0; r < GRID_SIZE; r++) {
    for (int c = 0; c < GRID_SIZE; c++) {
      grid[r][c].value = 0;
      grid[r][c].is_fixed = false;
      grid[r][c].is_correct = true; // neutral at start
    }
  }

  // Step 1: generate a valid full grid
  FillGrid(grid);

  // Step 2: save full solution for later access
  SaveSudokuGrid(grid, SOLUTION_FILE);

  // Step 3: remove cells based on the difficulty
  RemoveCells(grid, game_difficulty);
}

bool FillGrid(struct Cell grid[GRID_SIZE][GRID_SIZE]) {
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      if (grid[row][col].value == 0) {
        int nums[GRID_SIZE];
        for (int i = 0; i < GRID_SIZE; i++) nums[i] = i+1;

        // Shuffle numbers for randomness
        for (int i = GRID_SIZE - 1; i > 0; i--) {
          int j = rand() % (i + 1);
          int temp = nums[i];
          nums[i] = nums[j];
          nums[j] = temp;
        }

        for (int i = 0; i < GRID_SIZE; i++) {
          int num = nums[i];
          if (IsSafe(grid, row, col, num)) {
            grid[row][col].value = num;
            if (FillGrid(grid)) {
              return true;
            }
            grid[row][col].value = 0;
          }
        }

        return false; // no valid number -> backtrack
      }
    }
  }

  return true; // all cells filled
}

bool IsSafe(struct Cell grid[GRID_SIZE][GRID_SIZE], int row, int column, int number) {
  // row + column check
  for (int x = 0; x < GRID_SIZE; x++) {
    if (grid[row][x].value == number || grid[x][column].value == number) {
      return false; // Number already exists in row or column
    }
  }

  // 3x3 box check
  int start_row = row - row % SUB_GRID_SIZE,
      start_column = column - column % SUB_GRID_SIZE;

  for (int r = 0; r < SUB_GRID_SIZE; r++) {
    for (int c = 0; c < SUB_GRID_SIZE; c++) {
      if (grid[start_row + r][start_column + c].value == number) {
        return false; // Number already exists in sub-grid
      }
    }
  }

  return true; // Number is valid
}

bool IsMoveCorrect(int row, int column, int number) {
  struct Cell solution[GRID_SIZE][GRID_SIZE];

  LoadSolutionGrid(solution, SOLUTION_FILE);

  return solution[row][column].value == number;
}

bool is_puzzle_solved(struct Cell grid[GRID_SIZE][GRID_SIZE]) {
  // All cells must be filled and respect Sudoku constraints
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      int value = grid[row][col].value;
      if (value == 0) {
        return false;
      }

      // Temporarily clear the cell and validate placement
      int backup = grid[row][col].value;
      grid[row][col].value = 0;
      bool valid = IsSafe(grid, row, col, value);
      grid[row][col].value = backup;

      if (valid == false) {
        return false;
      }
    }
  }

  return true;
}

void RemoveCells(struct Cell grid[GRID_SIZE][GRID_SIZE], enum GAME_DIFFICULTY game_difficulty) {
  // Map difficulty directly to cells to remove
  static const size_t difficulty_map[] = {
    CELLS_TO_REMOVE_EASY,   // difficulty 1
    CELLS_TO_REMOVE_MEDIUM, // difficulty 2
    CELLS_TO_REMOVE_HARD    // difficulty 3
  };

  size_t cells_to_remove = difficulty_map[game_difficulty];

  // Create an array of all valid cell positions
  size_t positions[GRID_SIZE * GRID_SIZE];
  for (size_t i = 0; i < GRID_SIZE * GRID_SIZE; i++)
    positions[i] = i;

  // Fisher-Yates shuffle to randomize cell removal order
  for (size_t i = GRID_SIZE * GRID_SIZE - 1; i > 0; i--) {
    size_t j = rand() % (i + 1),
           temp = positions[i];
    positions[i] = positions[j];
    positions[j] = temp;
  }

  // Remove cells using the shuffled positions
  for (size_t i = 0; i < cells_to_remove; i++) {
    size_t pos = positions[i],
           row = pos / GRID_SIZE,
           col = pos % GRID_SIZE;

    grid[row][col].value = 0;        // clear number
    grid[row][col].is_fixed = false; // mark as editable
    grid[row][col].is_correct = true; // empty = neutral
  }

  // mark the remaining non-empty cells as fixed and correct
  for (int r = 0; r < GRID_SIZE; r++) {
    for (int c = 0; c < GRID_SIZE; c++) {
      if (grid[r][c].value != 0) {
        grid[r][c].is_fixed = true;
        grid[r][c].is_correct = true;
      }
    }
  }
}

static void BuildSavePath(struct Player *player, char out_path[256]) {
  snprintf(out_path, 256, "%s%s.txt", GAME_STATE_SAVE_DIRECTORY, player->name);
}

bool SaveGameState(struct Player *player, enum GAME_DIFFICULTY game_difficulty, struct Cell grid[GRID_SIZE][GRID_SIZE]) {
  char path[256];
  BuildSavePath(player, path);

  FILE *file = fopen(path, "w");

  if (file == NULL) {
    return false;
  }

  fprintf(file, "DIFFICULTY %d\n", (int) game_difficulty);
  fprintf(file, "MISTAKES %d\n", player->mistakes);
  double elapsed = GetTime() - player->start_time;
  fprintf(file, "ELAPSED %.3f\n", elapsed);

  for (int r = 0; r < GRID_SIZE; r++) {
    for (int c = 0; c < GRID_SIZE; c++) {
      struct Cell *cell = &grid[r][c];

      fprintf(file, "%d:%d:%d%s", cell->value, (cell->is_fixed)? 1 : 0, (cell->is_correct)? 1 : 0, (c == GRID_SIZE - 1)? "": " ");
    }
    fprintf(file, "\n");
  }

  fclose(file);
  return true;
}

bool LoadGameState(struct Player *player, enum GAME_DIFFICULTY *game_difficulty, struct Cell grid[GRID_SIZE][GRID_SIZE]) {
  char path[256];
  BuildSavePath(player, path);

  FILE *file = fopen(path, "r");

  if (file == NULL) {
    return false;
  }

  int difficulty = 0,
      mistakes = 0;
  double saved_elapsed = 0.0;

  if (fscanf(file, "DIFFICULTY %d\n", &difficulty) != 1) {
    fclose(file);
    return false;
  }
  if (fscanf(file, "MISTAKES %d\n", &mistakes) != 1) {
    fclose(file);
    return false;
  }
  if (fscanf(file, "ELAPSED %lf\n", &saved_elapsed) != 1) {
    fclose(file);
    return false;
  }

  // Read grid lines
  for (int r = 0; r < GRID_SIZE; r++) {
    for (int c = 0; c < GRID_SIZE; c++) {
      int v, fxd, corr;
      if (fscanf(file, "%d:%d:%d", &v, &fxd, &corr) != 3) {
        fclose(file);
        return false;
      }

      grid[r][c].value = v;
      grid[r][c].is_fixed = (fxd != 0);
      grid[r][c].is_correct = (corr != 0);

      if (c < (GRID_SIZE - 1)) {
        int ch = fgetc(file);

        if (ch != ' ') {
          ungetc(ch, file);
        }
      }
    }
    int ch;
    while ((ch = fgetc(file)) != '\n' && ch != EOF) {}
  }

  fclose(file);

  *game_difficulty = (enum GAME_DIFFICULTY) difficulty;
  player->mistakes = mistakes;
  player->start_time = GetTime() - saved_elapsed;

  return true;
}

bool DeleteGameState(struct Player *player) {
  char path[256];
  BuildSavePath(player, path);
  return remove(path) == 0;
}
