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
#include "../header/main_test.h"

MU_TEST(test_maze_init_finish) {
  maze_ maze;

  maze.height = 0;
  maze.width = 0;
  mu_check(is_init(maze) == 0);

  maze.height = MIN_MAZE_SIZE;
  maze.width = MIN_MAZE_SIZE;
  mu_check(is_init(maze) == 1);

  mu_check(is_finished(maze, maze.height - 2, maze.width - 1) == 1);
}

MU_TEST(test_maze_valid_size) {
  mu_check(is_valid_size(MIN_MAZE_SIZE - 1) == 0);
  mu_check(is_valid_size(MIN_MAZE_SIZE) == 1);
  mu_check(is_valid_size(MAX_MAZE_SIZE - 1) == 0);
  mu_check(is_valid_size(MAX_MAZE_SIZE) == 1);
}

MU_TEST(test_maze_locdirection) {
  int line;
  int column;

  line = 3;
  column = 3;
  convert_location_direction(&line, &column, 0);
  mu_check(line == 2 && column == 3);
  convert_location_direction(&line, &column, 1);
  mu_check(line == 2 && column == 4);
  convert_location_direction(&line, &column, 2);
  mu_check(line == 3 && column == 4);
  convert_location_direction(&line, &column, 3);
  mu_check(line == 3 && column == 3);
}

MU_TEST(test_generation) {
  maze_ maze;
  cell_** cells;
  int line;
  int column;
  int sum_abs_score;
  cell_ cell;

  maze.width = 11;
  maze.height = 11;
  maze.difficulty = HARD;
  cells = allocte_cells_line(maze);

  mu_check(is_generated(maze, cells) == 0);
  generate_maze(&maze, cells);
  mu_check(is_generated(maze, cells) == 1);

  for (line = 0; line < maze.height; line++) {
    for (column = 0; column < maze.width; column++) {
      cell = cells[line][column];
      sum_abs_score += abs(cell.score_value);
    }
  }

  mu_check(sum_abs_score > 0);

  free(cells);
}

MU_TEST(test_monster) {
  maze_ maze;
  cell_** cells;
  cell_ fake_cell;
  cell_* cell;
  monster_ monster;

  maze.width = 11;
  maze.height = 11;
  maze.difficulty = HARD;
  monster.type = GHOST;
  monster.move_monster = move_ghost;
  cells = allocte_cells_line(maze);
  generate_maze(&maze, cells);
  cell = &fake_cell; /* Will be not read, only set by is_valid_case function */

  monster.init_line = 1;
  monster.init_column = 0;
  monster.line = monster.init_line;
  monster.column = monster.init_column;
  mu_check(is_valid_case(maze, &monster, 3, &cell, cells) == 0);
  mu_check(is_valid_case(maze, &monster, 1, &cell, cells) == 1);

  free(cells);
}

MU_TEST(test_player) {
  maze_ maze;
  cell_** cells;
  player_ player;
  int i;
  wchar_t valid_moves[] = {L'z', L'q', L's', L'd'};
  int nb_valid_moves = 4;

  maze.height = MIN_MAZE_SIZE;
  maze.width = MIN_MAZE_SIZE;
  player.line = 0;
  player.column = 0;

  cells = allocte_cells_line(maze);
  generate_maze(&maze, cells);
  mu_check(get_empty_cell(0, 0, maze, cells) == NULL);
  mu_check(get_empty_cell(1, 0, maze, cells) != NULL);

  tp_player_entrance(&player);
  mu_check(player.line == 1 && player.column == 0);

  for (i = 0; i < nb_valid_moves; i++) {
    mu_check(is_valid_movement_char(valid_moves[i]) == 1);
    mu_check(can_move(valid_moves[i], &player, maze, cells) == (i == 3));
  }

  free(cells);
}

MU_TEST(test_files_management) {
  maze_ maze;
  cell_** cells;
  char test_name[NAME_MAZE_LENGTH] = "start_<>?/.:/\"*\\|_end";

  maze.height = MIN_MAZE_SIZE;
  maze.width = MIN_MAZE_SIZE;
  maze.monster_maze = 0;
  maze.difficulty = 0;
  strcpy(maze.name, test_name);

  cells = allocte_cells_line(maze);
  generate_maze(&maze, cells);

  init_score(&maze);
  save_maze(maze, cells);
  save_maze_score(&maze);
  mu_check(is_regular_file(get_save_file_path(maze.name)) == 1);
  mu_check(is_regular_file(get_score_file_path(maze.name)) == 1);

  free(cells);
  cells = load_maze(&maze);
  mu_check(cells != NULL);
  mu_check(maze.height == MIN_MAZE_SIZE && maze.width == MIN_MAZE_SIZE);
  mu_check(maze.difficulty == 0 && maze.monster_maze == 0);

  delete_maze_save(maze);
  delete_maze_score(maze);
}

MU_TEST_SUITE(test_suite) {
  MU_RUN_TEST(test_maze_init_finish);
  MU_RUN_TEST(test_maze_valid_size);
  MU_RUN_TEST(test_maze_locdirection);
  MU_RUN_TEST(test_generation);
  MU_RUN_TEST(test_monster);
  MU_RUN_TEST(test_player);
  MU_RUN_TEST(test_files_management);
}

void run_tests() {
  load_config_values();
  MU_RUN_SUITE(test_suite);
  MU_REPORT();
}

int main(void) {
  srand(time(NULL));
  setlocale(LC_ALL, "");

  run_tests();
  return MU_EXIT_CODE;
}