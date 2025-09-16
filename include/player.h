#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include "./config.h"

#define PLAYERS_FILE "../data/players.csv"

#define MIN_NAME_LENGTH 4
#define MAX_NAME_LENGTH 10
#define MIN_PASSWORD_LENGTH 8
#define MAX_PASSWORD_LENGTH 20

// Player structure (with attributes and methods)
struct Player {
  // Player attributes
  char *name;
  char *password;
  int mistakes;
  double start_time;

  // Player methods
  void (*SetName)(struct Player *self);
  void (*SetPassword)(struct Player *self);
  void (*SavePlayer)(struct Player *self);
  void (*FreePlayer)(struct Player *self);
};

// Function used to create and initialize a new player structure
extern struct Player *CreatePlayer();

// Function used to set up function pointers for player methods
extern void SetPlayerMethods(struct Player *player);

// Function used to read and set the name for a player
extern void SetName(struct Player *self);

// Function used to validate the name in real time
extern void ValidateNameInRealTime(const char *name, struct ValidationResult *name_validation);

// Function used to read and set the password for a player
extern void SetPassword(struct Player *self);

// Function used to validate the password in real time
extern void ValidatePasswordInRealTime(const char *password, struct ValidationResult *password_validation);

// Function used to check if a string contains only the allowed characters
extern bool ContainsOnlyAllowedChars(const char *str);

// Function used to check if a string has a valid length
extern bool HasValidLength(const char *str, size_t min, size_t max);

// Function used to check if a string has no consecutive spaces
extern bool HasNoConsecutiveSpaces(const char *str);

// Function used to check if a string has no leading or trailing spaces
extern bool HasNoLeadingOrTrailingSpaces(const char *str);

// Function used to save the player info into a csv file
extern void SavePlayer(struct Player *self);

// Function used to free the memory allocated to a player structure
extern void FreePlayer(struct Player *self);
