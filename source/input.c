#include "../include/input.h"

bool read_user_input(uint8_t *input) {
  char extra; // Variable to store the extra characters read from the user
  if (scanf("%hhu%c", &(*input), &extra) != 2 || extra != '\n') {
    (*input) = 0; // Set the input to 0
    clear_input_buffer();
    return false; // Input not read successfully from the user
  }

  return true; // Input read successfully from the user
}

void clear_input_buffer() {
  int c; // Variable to store the characters read from the user
  while ((c = getchar()) != '\n' && c != EOF); // clear the input buffer until a newline character or an end of file is encountered
}