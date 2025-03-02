#include "../include/player.h"

struct Player *CreatePlayer() {
  // Allocate memory for the player
  struct Player *player = (struct Player*) malloc(1 * sizeof(struct Player));

  // Check if the player's memory allocation was successful
  if (player == NULL) {
    TraceLog(LOG_ERROR, "Failed to allocate memory for the player!");
    return NULL;
  }

  // Allocate memory for the player's attributes
  player->name = (char *) malloc(sizeof(char) * (MAX_NAME_LENGTH + 1));
  player->password = (char *) malloc(sizeof(char) * (MAX_PASSWORD_LENGTH + 1));

  // Check if the player's attributes memory allocation was successful
  if (player->name == NULL || player->password == NULL) {
    TraceLog(LOG_ERROR, "Failed to allocate memory for the player's attributes!");
    player->FreePlayer(player);
    return NULL;
  }

  // Set the player's methods
  SetPlayerMethods(player);

  // Return the pointer to the player
  return player;
}

void SetPlayerMethods(struct Player *self) {
  // Assign the function pointers to the player methods
  self->SetName = SetName;
  self->SetPassword = SetPassword;
  self->SavePlayer = SavePlayer;
  self->FreePlayer = FreePlayer;
}

void SetName(struct Player *self) {
  // Get the key pressed by the player
  int key = GetKeyPressed();

  // Process all pressed keys
  while (key > 0) {
    // Check if the key is a printable character and within the max length limit
    if (key >= 32 && key <= 126 && strlen(self->name) < MAX_NAME_LENGTH) {
      // Get the current length of the name
      size_t length = strlen(self->name);

      // Append the new character
      self->name[length] = (char) key;

      // Null-terminate the string
      self->name[length + 1] = '\0';
    }
    else if (key == KEY_BACKSPACE && strlen(self->name) > 0) // Handle backspace: Remove the last character if the string is not empty
      self->name[strlen(self->name) - 1] = '\0';

    // Check for the next key press
    key = GetKeyPressed();
  }
}

void SetPassword(struct Player *self) {
  // Get the key pressed by the player
  int key = GetKeyPressed();

  // Process all pressed keys
  while (key > 0) {
    // Check if the key is a printable character and within the max length limit
    if (key >= 32 && key <= 126 && strlen(self->password) < MAX_PASSWORD_LENGTH) {
      // Get the current length of the password
      size_t length = strlen(self->password);

      // Append the new character
      self->password[length] = (char) key;

      // Null-terminate the string
      self->password[length + 1] = '\0';
    }
    else if (key == KEY_BACKSPACE && strlen(self->password) > 0) // Handle backspace: Remove the last character if the string is not empty
      self->password[strlen(self->password) - 1] = '\0';

    // Check for the next key press
    key = GetKeyPressed();
  }
}

void SavePlayer(struct Player *self) {
  // Open the players' file in append mode to add a new player
  FILE *file = fopen(PLAYERS_FILE, "a");

  // Check if the file openned successfully
  if (file == NULL) {
    TraceLog(LOG_ERROR, "Unable to open the players' file!");
    return;
  }

  // Write the player's data into the file
  fprintf(file, "%s,%s\n", self->name, self->password);

  // Close the file after writing
  fclose(file);
}

void FreePlayer(struct Player *self) {
  // Check if the player structure is valid
  if (self == NULL) {
    TraceLog(LOG_ERROR, "Invalid player structure");
    return;
  }

  if (self->name != NULL) {
    free(self->name); // Free the name memory
    self->name = NULL;
  }
  if (self->password != NULL) {
    free(self->password); // Free the password memory
    self->password = NULL;
  }
  free(self); // Free the player memory
  self = NULL;
}