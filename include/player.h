#pragma once

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "./config.h"

#define PLAYERS_FILE "../data/players.csv"

#define MAX_NAME_LENGTH 10
#define MAX_PASSWORD_LENGTH 20

// Player structure (with attributes and methods)
struct Player {
  // Player attributes
  char *name;
  char *password;

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

// Function used to read and set the password for a player
extern void SetPassword(struct Player *self);

// Function used to save the player info into a csv file
extern void SavePlayer(struct Player *self);

// Function used to free the memory allocated to a player structure
extern void FreePlayer(struct Player *self);