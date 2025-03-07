#include "../include/process.h"

void ProcessSignUpInput(struct Player *player, enum GAME_STATE *game_state, Rectangle name_box, bool *isNameBoxActive, Rectangle password_box, bool *isPasswordBoxActive, Rectangle log_in_box, Rectangle sign_up_button, bool *isNameEmpty, bool *isPasswordEmpty, bool *isNameUnique) {
  // Get the current mouse position
  Vector2 mouse_position = GetMousePosition();

  // Check if the mouse is inside one of the boxes and clicked with the left mouse button
  if (CheckCollisionPointRec(mouse_position, name_box) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
    (*isNameBoxActive) = true;
    (*isPasswordBoxActive) = false;
  }
  else if (CheckCollisionPointRec(mouse_position, password_box) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
    (*isNameBoxActive) = false;
    (*isPasswordBoxActive) = true;
  }
  else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    (*isNameBoxActive) = false;
    (*isPasswordBoxActive) = false;
  }

  // Handle text input when the box is active
  if ((*isNameBoxActive) == true && (*isPasswordBoxActive) == false)
    player->SetName(player);
  else if ((*isNameBoxActive) == false && (*isPasswordBoxActive) == true)
    player->SetPassword(player);

  // Check for click
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(GetMousePosition(), log_in_box) == true) {
    ChangeGameState(game_state, LOG_IN);

    // Clear the 'name' and 'password' fields by setting all bytes to '\0'
    memset(player->name, '\0', MAX_NAME_LENGTH);
    memset(player->password, '\0', MAX_PASSWORD_LENGTH);
  }

  // Check if the Sign Up button was clicked
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(mouse_position, sign_up_button) == true) {
    // Validate name input
    (*isNameEmpty) = (strlen(player->name) == 0);

    // Validate password input
    (*isPasswordEmpty) = (strlen(player->password) == 0);

    // Only proceed if both fields are filled
    if ((*isNameEmpty) == false && (*isPasswordEmpty) == false) {
      if (isNameTaken(player->name) == true)
        (*isNameUnique) = false;
      else {
        (*isNameUnique) = true;
        player->SavePlayer(player); // Save the player's info to the plauer's file
        ChangeGameState(game_state, MAIN_MENU);
      }
    }
  }
}

void ProcessLogInInput(struct Player *player, enum GAME_STATE *game_state, Rectangle name_box, bool *isNameBoxActive, Rectangle password_box, bool *isPasswordBoxActive, Rectangle sign_up_box, Rectangle log_in_button, bool *isNameEmpty, bool *isPasswordEmpty) {
  // Get the current mouse position
  Vector2 mouse_position = GetMousePosition();

  // Check if the mouse is inside one of the boxes and clicked with the left mouse button
  if (CheckCollisionPointRec(mouse_position, name_box) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
    (*isNameBoxActive) = true;
    (*isPasswordBoxActive) = false;
  }
  else if (CheckCollisionPointRec(mouse_position, password_box) == true && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true) {
    (*isNameBoxActive) = false;
    (*isPasswordBoxActive) = true;
  }
  else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    (*isNameBoxActive) = false;
    (*isPasswordBoxActive) = false;
  }

  // Handle text input when the box is active
  if ((*isNameBoxActive) == true && (*isPasswordBoxActive) == false)
    player->SetName(player);
  else if ((*isNameBoxActive) == false && (*isPasswordBoxActive) == true)
    player->SetPassword(player);

  // Check for click
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(GetMousePosition(), sign_up_box) == true) {
    ChangeGameState(game_state, SIGN_UP);

    // Clear the 'name' and 'password' fields by setting all bytes to '\0'
    memset(player->name, '\0', MAX_NAME_LENGTH);
    memset(player->password, '\0', MAX_PASSWORD_LENGTH);
  }

  // Check if the Log In button was clicked
  if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) == true && CheckCollisionPointRec(mouse_position, log_in_button) == true) {
    // Validate name input
    (*isNameEmpty) = (strlen(player->name) == 0);

    // Validate password input
    (*isPasswordEmpty) = (strlen(player->password) == 0);

    // Only proceed if both fields are filled
    if ((*isNameEmpty) == false && (*isPasswordEmpty) == false)
      ChangeGameState(game_state, MAIN_MENU);
  }
}