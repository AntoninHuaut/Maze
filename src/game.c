#include "../header/game.h"

void start_game(maze_ maze, cell_** cells) {
  player_ player;
  int last_round;
  int count_movement;
  last_round = 1;
  count_movement = 0;

  player.line = 1;
  player.column = 0;

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
  wait_user_interaction();
}

int play_round(maze_ maze, player_* player, cell_** cells) {
  char movement;
  movement = ask_movement();

  if (!can_move(movement, player, maze, cells)) {
    return 0;
  }

  return 1;
}