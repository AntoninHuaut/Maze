#include "../header/utils.h"

void wait_user_interaction() {
  wprintf(L"%sPress [enter] to continue%s\n", BLACK_BRIGHT, RESET);
  getchar();
}

void ask_value_int(int* var) {
  if (scanf("%d", var) < 1) {
    clear_buffer();
    wprintf(L"%sYou must type a number%s: ", RED, RESET);
    ask_value_int(var);
  } else {
    clear_buffer();
  }
}

void clear_buffer() {
  int c;
  do {
    c = getchar();
  } while (c != '\n' && c != EOF);
}

/* https://www.gnu.org/software/libc/manual/html_node/Noncanon-Example.html */
#include <termios.h>
#include <unistd.h>

/* Use this variable to remember original terminal attributes. */
struct termios saved_attributes;

void reset_input_mode(void) {
  tcsetattr(STDIN_FILENO, TCSANOW, &saved_attributes);
}

void set_input_mode(void) {
  struct termios tattr;

  /* Make sure stdin is a terminal. */
  if (!isatty(STDIN_FILENO)) {
    fprintf(stderr, "Not a terminal.\n");
    exit(EXIT_FAILURE);
  }

  /* Save the terminal attributes so we can restore them later. */
  tcgetattr(STDIN_FILENO, &saved_attributes);
  atexit(reset_input_mode);

  /* Set the funny terminal modes. */
  tcgetattr(STDIN_FILENO, &tattr);
  tattr.c_lflag &= ~(ICANON | ECHO); /* Clear ICANON and ECHO. */
  tattr.c_cc[VMIN] = 1;
  tattr.c_cc[VTIME] = 0;
  tcsetattr(STDIN_FILENO, TCSAFLUSH, &tattr);
}
/* */