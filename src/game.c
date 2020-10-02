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
#include "../header/game.h"

void start_game(maze_* maze, cell_** cells) {
  player_ player;
  int last_round;
  int player_eaten;
  last_round = 1;

  player.line = 1;
  player.column = 0;
  player.bonus_score = 0;
  player.moves = 0;

  wprintf(L"\n");

  while (!is_finished(*maze, player.line, player.column)) {
    display(*maze, cells, player);
    wprintf(L"Score: %-3d\n", get_player_score(player));

    if (!last_round) {
      wprintf(L"%sYou can't move here!%s\n", RED, RESET);
    }

    last_round = play_round(*maze, &player, cells);
    player.moves += last_round;

    player_eaten = check_player_on_monster(&player, *maze);
    move_monsters(maze, cells);

    if (player_eaten) {
      tp_player_entrance(&player);
      wprintf(L"%sYou have been eaten by the monster!%s\n", RED, RESET);
      wait_user_interaction();
    }
  }

  display(*maze, cells, player);
  wprintf(L"You finish the maze in %d moves and with %d bonus points\n",
          player.moves, player.bonus_score);

  wprintf(L"%sScore: %d%s\n", GREEN, get_player_score(player), RESET);
  handle_new_score(maze, player);
  show_best_score(maze);
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