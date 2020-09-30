/**
 * ENSICAEN
 * 6 Boulevard Maréchal Juin
 * F-14050 Caen Cedex
 *
 * This file is owned by ENSICAEN students. No portion of this
 * document may be reproduced, copied or revised without written
 * permission of the authors.
 *
 * @author Antonin Huaut <antonin.huaut@ecole.ensicaen.fr>
 * @version 1.0.0 - 2020-09-30
 */
#include "../header/display.h"

void show_menu() {
  int answer;
  int has_save_files;
  maze_ maze = {0};
  cell_** cells = NULL;

  while (1) {
    system("clear");

    wprintf(L"%s Welcome to the Maze Game!%s\n", YELLOW, RESET);

    if (is_init(maze)) {
      wprintf(L"\nSettings:\n");
      wprintf(L"  Name: %s\n", maze.name);
      wprintf(L"  Size: %d*%d\n", maze.height, maze.width);
      wprintf(L"  Difficulty: %s\n", get_difficulty_by_num(maze.difficulty));
    }

    wprintf(L"\nOptions:\n");
    wprintf(L"  1. Create a maze\n");
    wprintf(L"  2. Load a maze\n");
    wprintf(L"  3. Play the maze\n");
    wprintf(L"  4. Quit\n\n");

    do {
      wprintf(L"Your choice (%d-%d): ", MIN_CHOICE, MAX_CHOICE);
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
          show_best_score(&maze);
        }

        wprintf(L"\n");
        wait_user_interaction();
        break;
      case 3:
        if (cells == NULL) {
          wprintf(L"%sYou need to load a maze%s\n", RED, RESET);
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
  wprintf(L"%sPress [enter] to continue%s\n", BLACK_BRIGHT, RESET);
  getchar();
}

void display(maze_ maze, cell_** cells) {
  int line;
  int column;
  system("clear");

  for (line = 0; line < maze.height; line++) {
    for (column = 0; column < maze.width; column++) {
      printf_symbol_color(cells[line][column].symbol);
      wprintf(L"%lc", cells[line][column].symbol);
    }

    wprintf(L"\n");
  }

  wprintf(L"%s", RESET);
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

void printf_symbol_color(wchar_t symbol) {
  wprintf(L"%s", RESET);

  /* Impossible to use switch on wchar_t const values */
  if (symbol == PLAYER_CHAR) {
    wprintf(L"%s", BLACK_BRIGHT_BACKGROUND);
    wprintf(L"%s", YELLOW);
  } else if (symbol == EMPTY_CHAR) {
    wprintf(L"%s", BLACK_BRIGHT_BACKGROUND);
  } else if (symbol == BONUS_CHAR) {
    wprintf(L"%s", BLACK_BRIGHT_BACKGROUND);
    wprintf(L"%s", GREEN);
  } else if (symbol == MALUS_CHAR) {
    wprintf(L"%s", BLACK_BRIGHT_BACKGROUND);
    wprintf(L"%s", RED);
  } else {
    wprintf(L"%s", BLACK_BACKGROUND);
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