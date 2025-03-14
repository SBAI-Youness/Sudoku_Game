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

  // Handle text input when the box is active
  if (name_box->isActive == true && password_box->isActive == false)
    player->SetName(player);
  else if (name_box->isActive == false && password_box->isActive == true)
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
    name_box->isEmpty = (strlen(player->name) == 0);

    // Validate password input
    password_box->isEmpty = (strlen(player->password) == 0);

    // Only proceed if both fields are filled
    if (name_box->isEmpty == false && password_box->isEmpty == false) {
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

  // Handle text input when the box is active
  if (name_box->isActive == true && password_box->isActive == false)
    player->SetName(player);
  else if (name_box->isActive == false && password_box->isActive == true)
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
    name_box->isEmpty = (strlen(player->name) == 0);

    // Validate password input
    password_box->isEmpty = (strlen(player->password) == 0);

    // Only proceed if both fields are filled
    if (name_box->isEmpty == false && password_box->isEmpty == false) {
      if (AuthenticatePlayer(player) == true) {
        (*isAuthenticated) = true;
        ChangeGameState(game_state, MAIN_MENU);
      }
      else
        (*isAuthenticated) = false;
    }
  }
}