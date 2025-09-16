#include "../include/play.h"

void HandlePlayingProcess(struct Player *player, enum GAME_STATE *game_state, enum GAME_DIFFICULTY game_difficulty, Texture2D pause_image_texture) {
  static struct Cell grid[GRID_SIZE][GRID_SIZE];
  static bool initialized = false,
              last_move_correct = true;
  static int selected_row = -1,
             selected_column = -1;

  if (initialized == false) {
    // seed random once
    srand((unsigned int)time(NULL));

    // Generate sudoku grid with given difficulty
    GenerateSudokuGrid(grid, game_difficulty);

    player->mistakes = 0;
    player->start_time = GetTime();

    initialized = true;
  }

  ProcessPlayingInput(player, grid, &selected_row, &selected_column, &last_move_correct);

  RenderPlayingPage(player, game_difficulty, pause_image_texture, grid, selected_row, selected_column, last_move_correct);

  if (player->mistakes >= 3) {
    ChangeGameState(game_state, EXIT);
  }

  if (is_puzzle_solved(grid) == true) {
    ChangeGameState(game_state, MAIN_MENU);
  }
}

void GenerateSudokuGrid(struct Cell grid[GRID_SIZE][GRID_SIZE], enum GAME_DIFFICULTY game_difficulty) {
  // Step 1: generate a valid full grid
  FillGrid(grid);

  // Step 2: save full solution for later access
  SaveSudokuGrid(grid, SOLUTIONS_FILE);

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

bool IsMoveCorrect(struct Cell grid[GRID_SIZE][GRID_SIZE], int row, int column, int number) {
  // Temporarily clear the cell
  int backup = grid[row][column].value;
  grid[row][column].value = 0;

  bool valid = IsSafe(grid, row, column, number);

  // Restore the value
  grid[row][column].value = backup;

  return valid;
}

bool is_puzzle_solved(struct Cell grid[GRID_SIZE][GRID_SIZE]) {
  for (size_t row = 0; row < GRID_SIZE; row++) {
    for (size_t col = 0; col < GRID_SIZE; col++) {
      if (grid[row][col].value == 0) {
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

    grid[row][col].value = 0;     // clear number
    grid[row][col].is_fixed = false; // mark as editable
  }

  // mark the remaining non-empty cells as fixed
  for (int r = 0; r < GRID_SIZE; r++) {
    for (int c = 0; c < GRID_SIZE; c++) {
      if (grid[r][c].value != 0) {
        grid[r][c].is_fixed = true;
      }
    }
  }
}
