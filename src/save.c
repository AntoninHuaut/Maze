#include "../header/save.h"

/*
  https://www.zentut.com/c-tutorial/c-write-text-file/
  https://www.tutorialspoint.com/c_standard_library/c_function_fprintf.htm
*/
/* https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm */

char* replace_char(char* str, char find, char replace) {
  char* current_pos;

  current_pos = strchr(str, find);
  while (current_pos) {
    *current_pos = replace;
    current_pos = strchr(current_pos, find);
  }

  return str;
}

char* get_file_name(maze_ maze) {
  char* file_name;
  char forbidden_char[] = {' ', '/', '\\', '>', '<', ':', '|', '"', '?', '*'};
  int forbidden_char_length;
  char safe_maze_name[NAME_MAZE_LENGTH];
  int index;

  forbidden_char_length = sizeof(forbidden_char) / sizeof(char);

  strcpy(safe_maze_name, maze.name);
  file_name = (char*)malloc(strlen(SAVE_FOLDER) + strlen(safe_maze_name) +
                            strlen(SAVE_EXT) + 1);

  if (file_name == NULL) {
    perror(RED "Malloc error save_maze");
    exit(1);
  }

  for (index = 0; index < forbidden_char_length; index++) {
    replace_char(safe_maze_name, forbidden_char[index], '_');
  }

  strcpy(file_name, SAVE_FOLDER);
  strcat(file_name, safe_maze_name);
  strcat(file_name, SAVE_EXT);

  return file_name;
}

void save_maze(maze_ maze, cell_** cells) {
  FILE* file;
  struct stat folder_stat;
  char* file_name;
  int line;
  int column;

  if (stat(SAVE_FOLDER, &folder_stat) == -1) {
    mkdir(SAVE_FOLDER, 0700);
  }

  file_name = get_file_name(maze);
  file = fopen(file_name, "w");
  free(file_name);

  if (file == NULL) {
    fprintf(stderr, RED "Impossible to save the maze\n" RESET);
    wait_user_interaction();
    return;
  }

  fprintf(file, "%s\n", maze.name);
  fprintf(file, "%d\n", maze.height);
  fprintf(file, "%d\n", maze.width);
  fprintf(file, "%d\n", maze.difficulty);

  for (line = 0; line < maze.height; line++) {
    for (column = 0; column < maze.width; column++) {
      fprintf(file, "%d\n", cells[line][column].number);
      fprintf(file, "%d\n", cells[line][column].symbol);
    }
  }

  fclose(file);
}

cell_** load_maze(maze_* maze) {
  maze_ tmp_maze;

  FILE* file;
  cell_** cells;
  char* file_name;
  int line;
  int column;
  int value_tmp;

  printf("\n");
  ask_maze_name(&tmp_maze);
  file_name = get_file_name(tmp_maze);
  file = fopen(file_name, "r");
  free(file_name);

  if (file == NULL) {
    fprintf(stderr, RED "This save file don't exist\n" RESET);
    wait_user_interaction();
    return NULL;
  }

  fgets(maze->name, NAME_MAZE_LENGTH, file);
  strtok(maze->name, "\n");

  fscanf(file, "%d\n", &(maze->height));
  fscanf(file, "%d\n", &(maze->width));
  fscanf(file, "%d\n", &value_tmp);
  maze->difficulty = value_tmp;

  cells = allocte_cells_line(*maze);

  for (line = 0; line < maze->height; line++) {
    for (column = 0; column < maze->width; column++) {
      fscanf(file, "%d\n", &(cells[line][column].number));
      fscanf(file, "%d\n", &value_tmp);
      cells[line][column].symbol = value_tmp;
    }
  }

  fclose(file);

  printf(GREEN "The maze was loaded with success\n" RESET);
  wait_user_interaction();

  return cells;
}