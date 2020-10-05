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
    wprintf(L"%s", CLEAR);

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
    wprintf(L"  4. Glossary\n");
    wprintf(L"  5. Quit\n\n");

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
          if (cells != NULL) {
            show_best_score(&maze);
          } else if (is_init(maze)) { /* Load old maze if valid */
            wprintf(L"\nReloading old maze\n");
            load_maze(&maze);
          }
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
        printf_symbol_color(WALL_CHAR);
        wprintf(L"\n%lc%s Wall\n", WALL_CHAR, RESET);

        printf_symbol_color(EMPTY_CHAR);
        wprintf(L"%lc%s Path\n", EMPTY_CHAR, RESET);

        printf_symbol_color(PLAYER_CHAR);
        wprintf(L"%lc%s You\n", PLAYER_CHAR, RESET);

        printf_symbol_color(BONUS_CHAR);
        wprintf(L"%lc%s Treasure\n", BONUS_CHAR, RESET);

        printf_symbol_color(MALUS_CHAR);
        wprintf(L"%lc%s Trap\n", MALUS_CHAR, RESET);

        printf_symbol_color(GHOST_CHAR);
        wprintf(L"%lc%s Ghost\n", GHOST_CHAR, RESET);

        printf_symbol_color(OGRE_CHAR);
        wprintf(L"%lc%s Ogre\n\n", OGRE_CHAR, RESET);

        wait_user_interaction();
        break;
      case 5:
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

void display(maze_ maze, cell_** cells, player_ player) {
  int line;
  int column;
  wchar_t symbol_display;
  monster_* monster;
  wprintf(L"%s", CLEAR);

  for (line = 0; line < maze.height; line++) {
    for (column = 0; column < maze.width; column++) {
      monster = get_monster_on_case(maze, line, column);

      if (monster != NULL) {
        symbol_display = get_symbol_monster_cell(*monster);
      } else if (player.line == line && player.column == column) {
        symbol_display = PLAYER_CHAR;
      } else {
        symbol_display = cells[line][column].symbol;
      }

      printf_symbol_color(cells[line][column].symbol);
      wprintf(L"%lc", symbol_display);
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

  if (symbol == WALL_CHAR) {
    wprintf(L"%s", BLACK_BACKGROUND);
  } else {
    wprintf(L"%s", WHITE_BACKGROUND);
  }
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