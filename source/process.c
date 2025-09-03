#include "../include/process.h"

void ProcessSignUpInput(struct Player *player, enum GAME_STATE *game_state, struct InputBox *name_box, bool *isNameUnique, struct InputBox *password_box, Rectangle log_in_box, Rectangle sign_up_button) {
  // Get the current mouse position
  Vector2 mouse_position = GetMousePosition();

  // Check if the mouse is inside one of the boxes and clicked with the left mouse button
  if (CheckCollisionPointRec(mouse_position, name_box->box) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
    name_box->isActive = true;
    password_box->isActive = false;
  }
  else if (CheckCollisionPointRec(mouse_position, password_box->box) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
    name_box->isActive = false;
    password_box->isActive = true;
  }
  else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    name_box->isActive = false;
    password_box->isActive = false;
  }

  // Handle Tab key to switch between name and password input fields
  if (IsKeyPressed(KEY_TAB) == true) {
    if (name_box->isActive == false && password_box->isActive == false)
        name_box->isActive = true;  // Activate the name box if no input is active
    else if (name_box->isActive == true) {
      name_box->isActive = false;
      password_box->isActive = true;  // If name box is active, switch to password box
    }
    else if (password_box->isActive == true) {
        name_box->isActive = true;  // If password box is active, switch to name box
        password_box->isActive = false;
    }
  }

  // Handle text input when the box is active
  if (name_box->isActive == true && password_box->isActive == false) {
    player->SetName(player);
    ValidateNameInRealTime(player->name, &name_box->validation);
  }
  else if (name_box->isActive == false && password_box->isActive == true) {
    player->SetPassword(player);
    ValidatePasswordInRealTime(player->password, &password_box->validation);
  }

  // Check for click
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(GetMousePosition(), log_in_box) == true) {
    ChangeGameState(game_state, LOG_IN);

    // Clear the 'name' and 'password' fields by setting all bytes to '\0'
    memset(player->name, '\0', MAX_NAME_LENGTH);
    memset(player->password, '\0', MAX_PASSWORD_LENGTH);

    (*isNameUnique) = true;

    ResetInputBoxes(name_box, password_box);
  }

  // Check if the Sign Up button was clicked
  if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(mouse_position, sign_up_button) == true) || (password_box->isActive == true && IsKeyPressed(KEY_ENTER) == true)) {
    // Set isNameUnique to true by default
    (*isNameUnique) = true;

    // Validate the input fields
    ValidateNameInRealTime(player->name, &name_box->validation);
    ValidatePasswordInRealTime(player->password, &password_box->validation);

    // Only proceed if both fields are valid
    if (name_box->validation.isValid == true && password_box->validation.isValid == true) {
      if (isNameTaken(player->name) == true)
        (*isNameUnique) = false;
      else {
        player->SavePlayer(player);
        ChangeGameState(game_state, MAIN_MENU);
      }
    }
  }
}

void ProcessLogInInput(struct Player *player, enum GAME_STATE *game_state, struct InputBox *name_box, struct InputBox *password_box, bool *isAuthenticated, Rectangle sign_up_box, Rectangle log_in_button) {
  // Get the current mouse position
  Vector2 mouse_position = GetMousePosition();

  // Check if the mouse is inside one of the boxes and clicked with the left mouse button
  if (CheckCollisionPointRec(mouse_position, name_box->box) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
    name_box->isActive = true;
    password_box->isActive = false;
  }
  else if (CheckCollisionPointRec(mouse_position, password_box->box) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
    name_box->isActive = false;
    password_box->isActive = true;
  }
  else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    name_box->isActive = false;
    password_box->isActive = false;
  }

  // Handle Tab key to switch between name and password input fields
  if (IsKeyPressed(KEY_TAB) == true) {
    if (name_box->isActive == false && password_box->isActive == false)
        name_box->isActive = true;  // Activate the name box if no input is active
    else if (name_box->isActive == true) {
      name_box->isActive = false;
      password_box->isActive = true;  // If name box is active, switch to password box
    }
    else if (password_box->isActive == true) {
        name_box->isActive = true;  // If password box is active, switch to name box
        password_box->isActive = false;
    }
  }

  // Handle text input when the box is active
  if (name_box->isActive == true && password_box->isActive == false) {
    player->SetName(player);
    ValidateNameInRealTime(player->name, &name_box->validation);
  }
  else if (name_box->isActive == false && password_box->isActive == true) {
    player->SetPassword(player);
    ValidatePasswordInRealTime(player->password, &password_box->validation);
  }

  // Check for click
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(GetMousePosition(), sign_up_box) == true) {
    ChangeGameState(game_state, SIGN_UP);

    // Clear the 'name' and 'password' fields by setting all bytes to '\0'
    memset(player->name, '\0', MAX_NAME_LENGTH);
    memset(player->password, '\0', MAX_PASSWORD_LENGTH);

    (*isAuthenticated) = true;

    ResetInputBoxes(name_box, password_box);
  }

  // Check if the Log In button was clicked
  if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(mouse_position, log_in_button) == true) || (password_box->isActive == true && IsKeyPressed(KEY_ENTER))) {
    // Set isAuthenticated to true by default
    (*isAuthenticated) = true;

    // Validate fields
    ValidateNameInRealTime(player->name, &name_box->validation);
    ValidatePasswordInRealTime(player->password, &password_box->validation);

    // Only proceed if both fields are valid
    if (name_box->validation.isValid == true && password_box->validation.isValid == true) {
      if (AuthenticatePlayer(player) == true)
        ChangeGameState(game_state, MAIN_MENU);
      else
        (*isAuthenticated) = false;
    }
  }
}

void ProcessGameMenuInput(struct Player *player, enum GAME_STATE *game_state, Rectangle menu_buttons[], int menu_count, int *selected_button) {
  // Get the current mouse position
  Vector2 mouse_position = GetMousePosition();

  // Keyboard navigation
  if (IsKeyPressed(KEY_TAB)) {
    if (IsKeyDown(KEY_LEFT_SHIFT) || IsKeyDown(KEY_RIGHT_SHIFT)) {
      // Shift + Tab -> go backwards
      (*selected_button)--;
      if (*selected_button < 0) {
        *selected_button = menu_count - 1;
      }
    } else {
      // Normal Tab -> go forwards
      (*selected_button)++;
      if (*selected_button >= menu_count) {
        *selected_button = 0;
      }
    }
  }

  // If user presses Enter/Space, activate the selected button
  if (*selected_button >= 0 && IsKeyPressed(KEY_ENTER)) {
    HandleGameMenuAction(player, game_state, *selected_button);
  }

  for (int i = 0; i < menu_count; i++) {
    if (CheckCollisionPointRec(mouse_position, menu_buttons[i]) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
      *selected_button = i; // sync selection with mouse click

      HandleGameMenuAction(player, game_state, *selected_button);
    }
  }
}

void ProcessTutorialInput(enum GAME_STATE *game_state, Rectangle back_button) {
  // Get the current mouse position
  Vector2 mouse_position = GetMousePosition();

  if (CheckCollisionPointRec(mouse_position, back_button) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
    ChangeGameState(game_state, MAIN_MENU);
  }
}
