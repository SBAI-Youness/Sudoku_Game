#include "../include/auth.h"

void HandleSignUpProcess(struct Player *player, enum GAME_STATE *game_state, Texture2D game_icon_texture, Texture2D required_image_texture) {
  // Define and initialize input boxes for name and password fields
  static struct InputBox name_box = {
    .box = { (WINDOW_WIDTH / 2) - 200, 200, 400, 50},
    .isActive = false,
    .isValid = true
  },
  password_box = {
    .box = { (WINDOW_WIDTH / 2) - 200, 300, 400, 50},
    .isActive = false,
    .isValid = true
  };

  // Flag to track if the name is usique or not
  static bool isNameUnique = true;

  // Text to prompt the player to log in if they already have an account
  const char *text = "Already have an account? Log in";
  int text_width = MeasureText(text, 20), // Get text width dynamically
      text_x_position = (WINDOW_WIDTH / 2) + (name_box.box.width / 2) - text_width,
      text_y_position = password_box.box.y + password_box.box.height + 40;

  // Define the clickable area for the "Log in" text
  Rectangle log_in_box = { text_x_position, text_y_position, text_width, 20};

  // Define the "Sign Up" button position and size
  Rectangle sign_up_button = { (WINDOW_WIDTH / 2) - 75, log_in_box.y + log_in_box.height + 20, 150, 50};

  // Process the input for the sign up form (name and password)
  ProcessSignUpInput(player, game_state, &name_box, &isNameUnique, &password_box, log_in_box, sign_up_button);

  // Render the sign up page with the appropriate elements (input boxes, text, icon)
  RenderSignUpPage(player, game_icon_texture, required_image_texture, name_box, isNameUnique, password_box, log_in_box, (Vector2) { text_x_position, text_y_position}, text, sign_up_button);
}

void HandleLogInProcess(struct Player *player, enum GAME_STATE *game_state, Texture2D game_icon_texture, Texture2D required_image_texture) {
  // Define and initialize input boxes for name and password fields
  static struct InputBox name_box = {
    .box = { (WINDOW_WIDTH / 2) - 200, 200, 400, 50},
    .isActive = false,
    .isValid = true
  },
  password_box = {
    .box = { (WINDOW_WIDTH / 2) - 200, 300, 400, 50},
    .isActive = false,
    .isValid = true
  };

  // Flag to track if the player is authenticated or not
  static bool isAuthenticated = true;

  // Text to prompt the player to sign up if they don't have an account
  const char *text = "Don't have an account? Sign up";
  int text_width = MeasureText(text, 20), // Get text width dynamically
      text_x_position = (WINDOW_WIDTH / 2) + (name_box.box.width / 2) - text_width,
      text_y_position = password_box.box.y + password_box.box.height + 40;

  // Define the clickable area for the "Sign Up" text
  Rectangle sign_up_box = { text_x_position, text_y_position, text_width, 20};

  // Define the "Log In" button position and size
  Rectangle log_in_button = { (WINDOW_WIDTH / 2) - 75, sign_up_box.y + sign_up_box.height + 20, 150, 50};

  // Process the input for the log in form (name and password)
  ProcessLogInInput(player, game_state, &name_box, &password_box, &isAuthenticated, sign_up_box, log_in_button);

  // Render the log in page with the appropriate elements (input boxes, text, icon)
  RenderLogInPage(player, game_icon_texture, required_image_texture, name_box, password_box, isAuthenticated, sign_up_box, (Vector2) { text_x_position, text_y_position}, text, log_in_button);
}

bool isNameTaken(const char *name) {
  // Open the players' file to search for the player
  FILE *file = fopen(PLAYERS_FILE, "r");

  // Check if the file was opened successfully
  if (file == NULL) {
    TraceLog(LOG_ERROR, "Unable to open the players' file!");
    return false;
  }

  // TODO: Later on, I'm gonna need to skip the file's header ("Name,Password\n")

  // Temporary variable to store the player's name
  char temp_name[MAX_NAME_LENGTH + 1];

  while (fscanf(file, "%[^,],%*s\n", temp_name) != EOF)
    if (strcmp(temp_name, name) == 0) {
      fclose(file);
      return true; // Name is already taken
    }

  // Name not found
  fclose(file);
  return false; // Name is available
}

bool AuthenticatePlayer(struct Player *player) {
  // Open the players' file to search for the player
  FILE *file = fopen(PLAYERS_FILE, "r");

  // Check if the file was opened successfully
  if (file == NULL) {
    TraceLog(LOG_ERROR, "Unable to open the players' file.");
    return false;
  }

  char temp_name[MAX_NAME_LENGTH + 1],
       temp_password[MAX_PASSWORD_LENGTH + 1];

  while (fscanf(file, "%[^,],%[^\n]\n", temp_name, temp_password) != EOF)
    if (strcmp(temp_name, player->name) == 0 && strcmp(temp_password, player->password) == 0) {
        fclose(file);
        return true; // Authentication successful
    }

  fclose(file);
  return false; // Authentication failed
}