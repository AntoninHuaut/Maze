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
  player.nb_treasure = 0;
  player.poison_turn = 0;

  wprintf(L"\n");

  while (!is_finished(*maze, player.line, player.column)) {
    display(*maze, cells, player);
    if (player.poison_turn > 0) {
      wprintf(
          L"%sYou are poisoned for %d turn(s) : you can't see any treasures "
          L"and traps%s\n",
          PURPLE, player.poison_turn, RESET);
    }
    wprintf(L"%sScore: %-3d%s\n", YELLOW, get_player_score(player), RESET);

    if (!last_round) {
      wprintf(L"%sYou can't move here!%s\n", RED, RESET);
    }

    last_round = play_round(*maze, &player, cells);
    player.moves += last_round;

    /* Player walk on monster */
    player_eaten = check_player_on_monster(&player, *maze);
    if (player_eaten) {
      eat_player(*maze, cells, &player);
    }

    move_monsters(maze, cells);

    /* Monster walk on player */
    player_eaten = check_player_on_monster(&player, *maze);
    if (player_eaten) {
      eat_player(*maze, cells, &player);
    }

    if (player.poison_turn > 0) {
      player.poison_turn--;
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