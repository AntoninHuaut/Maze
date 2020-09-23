#include "../header/game.h"

void start_game(maze_ maze) {
  player_ player;
  cell_** cells;
  int last_round;
  int count_movement;
  count_movement = 0;

  cells = allocte_cells_line(maze);
  player.line = 1;
  player.column = 0;

  generate_maze(maze, cells);
  save_maze(maze, cells);
  printf("\n");

  while (!is_finished(maze, player.line, player.column)) {
    display(maze, cells);
    if (!last_round) {
      printf(RED "You can't move here!\n" RESET);
    }

    last_round = play_round(maze, &player, cells);
    count_movement += last_round;
  }

  display(maze, cells);
  printf(GREEN "You finish the maze in %d moves\n" RESET, count_movement);

  show_menu(maze);
}

int play_round(maze_ maze, player_* player, cell_** cells) {
  char movement;
  movement = ask_movement();

  if (!can_move(movement, player, maze, cells)) {
    return 0;
  }

  return 1;
}