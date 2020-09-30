/*
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
#include "../header/score.h"

char* get_score_file_path(char* maze_name) {
  char forbidden_char[] = {' ', '/', '\\', '>', '<', ':', '|', '"', '?', '*'};
  int forbidden_char_length;

  char* file_name;
  int index;
  int size_file;

  forbidden_char_length = sizeof(forbidden_char) / sizeof(char);

  size_file = strlen(maze_name) + strlen(SCORE_EXT);
  file_name = (char*)malloc(strlen(SCORE_FOLDER) + size_file + 1);

  if (file_name == NULL) {
    perror(RED "Malloc error save_maze");
    exit(1);
  }

  for (index = 0; index < forbidden_char_length; index++) {
    replace_char(maze_name, forbidden_char[index], '_');
  }

  strcpy(file_name, SCORE_FOLDER);
  strcat(file_name, maze_name);
  strcat(file_name, SCORE_EXT);

  return file_name;
}

void show_best_score(maze_* maze) {
  int index;

  printf(GREEN "Best score:\n" RESET);

  for (index = MAX_SCORE_MAZE - 1; index >= 0; index--) {
    if (maze->best_score[index].score != INT_MIN) {
      printf(YELLOW "%2d. " RESET "%s: %dpts\n", MAX_SCORE_MAZE - index,
             maze->best_score[index].name, maze->best_score[index].score);
    } else {
      printf("%2d. N/A\n", MAX_SCORE_MAZE - index);
    }
  }
}

void handle_new_score(maze_* maze, player_ player) {
  int best_score_index;
  int index;
  int player_score;
  char player_name[MAX_PLAYER_NAME_LENGTH];
  best_score_index = -1;
  player_score = get_player_score(player);

  for (index = 0; index < MAX_SCORE_MAZE; index++) {
    if (player_score > maze->best_score[index].score) {
      best_score_index = index;
    }
  }

  if (best_score_index == -1) {
    printf("\nYou don't have beat a record\n");
    wait_user_interaction();
    return;
  }

  printf("\nYou beat a record!\nPlease enter your name: ");

  do {
    fgets(player_name, MAX_PLAYER_NAME_LENGTH, stdin);
    strtok(player_name, "\n");
  } while (player_name[0] == '\n');

  printf("\n");

  for (index = 0; index < best_score_index; index++) {
    maze->best_score[index].score = maze->best_score[index + 1].score;
    strcpy(maze->best_score[index].name, maze->best_score[index + 1].name);
  }

  maze->best_score[best_score_index].score = player_score;
  strcpy(maze->best_score[best_score_index].name, player_name);

  save_maze_score(maze);
}

void delete_maze_score(maze_ maze) {
  remove(get_score_file_path(maze.name));
}

void save_maze_score(maze_* maze) {
  FILE* file;
  struct stat folder_stat;
  char* file_name;
  int index;

  if (stat(SCORE_FOLDER, &folder_stat) == -1) {
    mkdir(SCORE_FOLDER, 0700);
  }

  file_name = get_score_file_path(maze->name);
  file = fopen(file_name, "w");
  free(file_name);

  if (file == NULL) {
    fprintf(stderr, RED "Impossible to save best maze score\n" RESET);
    wait_user_interaction();
    return;
  }

  for (index = 0; index < MAX_SCORE_MAZE; index++) {
    fprintf(file, "%d\n", maze->best_score[index].score);

    if (maze->best_score[index].score == INT_MIN) {
      fprintf(file, "N/A\n");
    } else {
      fprintf(file, "%s\n", maze->best_score[index].name);
    }
  }

  fclose(file);
}

void load_maze_score(maze_* maze) {
  FILE* file;
  char* file_name;
  int index;

  file_name = get_score_file_path(maze->name);
  file = fopen(file_name, "r");
  free(file_name);

  if (file == NULL) {
    save_maze_score(maze);
    load_maze_score(maze);
    return;
  }

  for (index = 0; index < MAX_SCORE_MAZE; index++) {
    fscanf(file, "%d\n", &(maze->best_score[index].score));

    fgets(maze->best_score[index].name, MAX_PLAYER_NAME_LENGTH, file);
    strtok(maze->best_score[index].name, "\n");
  }

  fclose(file);
}