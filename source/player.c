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
  int key = GetCharPressed();

  while (key > 0) {
    if (key >= 32 && key <= 126 && strlen(self->name) < MAX_NAME_LENGTH) {
      size_t length = strlen(self->name);

      self->name[length] = (char) key;
      self->name[length + 1] = '\0';
    }

    key = GetCharPressed();
  }

  if (IsKeyPressed(KEY_BACKSPACE) == true && strlen(self->name) > 0)
    self->name[strlen(self->name) - 1] = '\0';
}

struct ValidationResult ValidateNameInRealTime(const char *name) {
  struct ValidationResult result = {
    .isValid = true,
    .error_message = NULL
  };

  if (name == NULL || strlen(name) == 0) {
    result.isValid = false;
    result.error_message = "Name cannot be empty";
    return result;
  }

  if (HasNoLeadingOrTrailingSpaces(name) == false) {
    result.isValid = false;
    result.error_message = "Name cannot begin or end with a space";
    return result;
  }

  if (HasNoConsecutiveSpaces(name) == false) {
    result.isValid = false;
    result.error_message = "Name cannot contain consecutive spaces";
    return result;
  }

  if (HasValidLength(name, MIN_NAME_LENGTH, MAX_NAME_LENGTH) == false) {
    result.isValid = false;
    result.error_message = "Name must contain between " STR(MIN_NAME_LENGTH) " and " STR(MAX_NAME_LENGTH) " characters";
    return result;
  }

  if (ContainsOnlyAllowedChars(name) == false) {
    result.isValid = false;
    result.error_message = "Name can only contain authorized letters, numbers and special characters";
    return result;
  }

  return result;
}

void SetPassword(struct Player *self) {
  int key = GetCharPressed();

  while (key > 0) {
    if (key >= 32 && key <= 126 && strlen(self->password) < MAX_PASSWORD_LENGTH) {
      size_t length = strlen(self->password);

      self->password[length] = (char) key;
      self->password[length + 1] = '\0';
    }

    key = GetCharPressed();
  }

  if (IsKeyPressed(KEY_BACKSPACE) == true && strlen(self->password) > 0)
    self->password[strlen(self->password) - 1] = '\0';
}

struct ValidationResult ValidatePasswordInRealTime(const char *password) {
  struct ValidationResult result = {
    .isValid = true,
    .error_message = NULL
  };

  if (password == NULL || strlen(password) == 0) {
    result.isValid = false;
    result.error_message = "Password cannot be empty";
    return result;
  }

  if (HasNoLeadingOrTrailingSpaces(password) == false) {
    result.isValid = false;
    result.error_message = "Password cannot begin or end with a space";
    return result;
  }

  if (HasNoConsecutiveSpaces(password) == false) {
    result.isValid = false;
    result.error_message = "Password cannot contain consecutive spaces";
    return result;
  }

  if (HasValidLength(password, MIN_PASSWORD_LENGTH, MAX_PASSWORD_LENGTH) == false) {
    result.isValid = false;
    result.error_message = "Password must contain between " STR(MIN_PASSWORD_LENGTH) " and " STR(MAX_PASSWORD_LENGTH) " characters";
    return result;
  }

  if (ContainsOnlyAllowedChars(password) == false) {
    result.isValid = false;
    result.error_message = "Password can only contain authorized letters, numbers and special characters";
    return result;
  }

  return result;
}

bool ContainsOnlyAllowedChars(const char *str) {
  if (str == NULL)
    return false;

  for (size_t i = 0; str[i] != '\0'; i++) {
    if (str[i] >= 32 && str[i] <= 126) {
      // Check if the character is a letter, number, or legal special character
      if (!isalnum(str[i]) && strchr(ALLOWED_SPECIAL_CHARACTERS, str[i]) == NULL)
        return false;
    }
    else
      return false;
  }

  return true;
}

bool HasValidLength(const char *str, size_t min, size_t max) {
  if (str == NULL)
    return false;

  size_t len = strlen(str);

  return len >= min && len <= max;
}

bool HasNoConsecutiveSpaces(const char *str) {
  if (str == NULL)
    return false;

  for (size_t i = 1; str[i] != '\0'; i++)
    if (str[i] == ' ' && str[i-1] == ' ')
      return false;

  return true;
}

bool HasNoLeadingOrTrailingSpaces(const char *str) {
  if (str == NULL)
    return false;

  return str[0] != ' ' && str[strlen(str) - 1] != ' ';
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