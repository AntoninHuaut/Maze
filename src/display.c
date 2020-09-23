#include "../header/display.h"

void show_menu(maze_ maze) {
  int answer;

  printf(YELLOW "\nWelcome to the Maze Game!\n" RESET);
  printf("Settings:\nName: %s\nSize: %d*%d\n", maze.name, maze.height,
         maze.width);

  printf("\nOptions:\n");
  printf("1. Change maze settings\n");
  printf("2. Play a random maze\n");
  printf("3. Load a maze\n");
  printf("4. Quit\n");

  do {
    printf("Your choice: ");
    ask_value_int(&answer);
  } while (answer < MIN_CHOICE || answer > MAX_CHOICE);

  switch (answer) {
    case 1:
      ask_maze_options(&maze);
      show_menu(maze);
      return;
    case 2:
      start_game(maze);
      break;
    case 3:
      load_maze(&maze);
      break;
    case 4:
      exit(0);
  }
}

void display(maze_ maze, cell_** cells) {
  int line;
  int column;
  /*system("clear");*/
  printf("system(\"clear\")\n");

  for (line = 0; line < maze.height; line++) {
    for (column = 0; column < maze.width; column++) {
      printf_symbol_color(cells[line][column].symbol);
      printf("%c", cells[line][column].symbol);
    }

    printf("\n");
  }

  printf(RESET);
}

void printf_symbol_color(char symbol) {
  printf(RESET);
  switch (symbol) {
    case 'o':
      printf(BLACK_BRIGHT_BACKGROUND);
      printf(YELLOW);
      break;
    case ' ':
      printf(BLACK_BRIGHT_BACKGROUND);
      break;
    default:
      printf(BLACK_BACKGROUND);
      break;
  }
}

void ask_value_int(int* var) {
  if (scanf("%d", var) < 1) {
    clear_buffer();
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