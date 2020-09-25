#include "../header/display.h"

void show_menu() {
  int answer;
  int has_save_files;
  maze_ maze = {0};
  cell_** cells = NULL;

  while (1) {
    system("clear");

    printf(YELLOW "Welcome to the Maze Game!\n" RESET);

    if (is_init(maze)) {
      printf("\nSettings:\n");
      printf("  Name: %s\n", maze.name);
      printf("  Size: %d*%d\n", maze.height, maze.width);
      printf("  Difficulty: %s\n", get_difficulty_by_num(maze.difficulty));
    }

    printf("\nOptions:\n");
    printf("  1. Create a maze\n");
    printf("  2. Load a maze\n");
    printf("  3. Play the maze\n");
    printf("  4. Quit\n\n");

    do {
      printf("Your choice: ");
      ask_value_int(&answer);
    } while (answer < MIN_CHOICE || answer > MAX_CHOICE);

    if (answer <= 2) {
      free_cells(maze, cells);
    }

    switch (answer) {
      case 1:
        cells = ask_maze_options(&maze);
        delete_maze_score(maze);
        init_score(&maze);
        break;
      case 2:
        has_save_files = show_save_files();

        if (has_save_files) {
          cells = load_new_maze(&maze);
        }

        printf("\n");
        show_best_score(&maze);
        wait_user_interaction();
        break;
      case 3:
        if (cells == NULL) {
          printf(RED "You need to load a maze\n" RESET);
          wait_user_interaction();
        } else {
          start_game(&maze, cells);
          free_cells(maze, cells);
          cells = load_maze(&maze);
        }
        break;
      case 4:
        free_cells(maze, cells);
        exit(0);
        break;
    }
  }
}

void wait_user_interaction() {
  printf(BLACK_BRIGHT "Press [enter] to continue\n" RESET);
  getchar();
}

void display(maze_ maze, cell_** cells) {
  int line;
  int column;
  system("clear");

  for (line = 0; line < maze.height; line++) {
    for (column = 0; column < maze.width; column++) {
      printf_symbol_color(cells[line][column].symbol);
      printf("%c", cells[line][column].symbol);
    }

    printf("\n");
  }

  printf(RESET);
}

char* get_difficulty_by_num(int difficulty) {
  switch (difficulty) {
    case 0:
      return "Normal";
    case 1:
      return "Hard";
    default:
      return "?";
  }
}

void printf_symbol_color(char symbol) {
  printf(RESET);
  switch (symbol) {
    case PLAYER_CHAR:
      printf(BLACK_BRIGHT_BACKGROUND);
      printf(YELLOW);
      break;
    case EMPTY_CHAR:
      printf(BLACK_BRIGHT_BACKGROUND);
      break;
    case BONUS_CHAR:
      printf(BLACK_BRIGHT_BACKGROUND);
      printf(GREEN);
      break;
    case MALUS_CHAR:
      printf(BLACK_BRIGHT_BACKGROUND);
      printf(RED);
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