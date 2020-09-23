#include "../header/save.h"

/*
  https://www.zentut.com/c-tutorial/c-write-text-file/
  https://www.tutorialspoint.com/c_standard_library/c_function_fprintf.htm
*/
/* https://www.tutorialspoint.com/c_standard_library/c_function_fscanf.htm */

char* get_file_name(maze_ maze) {
  char* file_name;

  file_name = (char*)malloc(strlen(SAVE_FOLDER) + strlen(maze.name) +
                            strlen(SAVE_EXT) + 1);
  if (file_name == NULL) {
    perror(RED "Malloc error save_maze");
    exit(1);
  }

  strcpy(file_name, SAVE_FOLDER);
  strcat(file_name, maze.name);
  strcat(file_name, SAVE_EXT);

  return file_name;
}

void save_maze(maze_ maze, cell_** cells) {
  FILE* file;
  struct stat folder_stat;
  char* file_name;

  if (stat(SAVE_FOLDER, &folder_stat) == -1) {
    mkdir(SAVE_FOLDER, 0700);
  }

  file_name = get_file_name(maze);
  file = fopen(file_name, "w");
  free(file_name);

  if (file == NULL) {
    fprintf(stderr, RED "Impossible to save the maze\n");
    return;
  }

  fprintf(file, "%s\n", maze.name);
  fprintf(file, "%d\n", maze.height);
  fprintf(file, "%d\n", maze.width);
  fprintf(file, "%d\n", maze.difficulty);

  maze.height++;
  cells[0][0].number++;

  fclose(file);
}

void load_maze(maze_* maze) {
  FILE* file;
  char* file_name;
  int value_tmp;

  file_name = get_file_name(*maze);
  file = fopen(file_name, "r");
  free(file_name);

  if (file == NULL) {
    fprintf(stderr, RED "This save file don't exist\n");
    show_menu(*maze);
    return;
  }

  fgets(maze->name, NAME_MAZE_LENGTH, file);
  strtok(maze->name, "\n");

  fscanf(file, "%d\n", &(maze->height));
  fscanf(file, "%d\n", &(maze->width));
  fscanf(file, "%d\n", &value_tmp);
  maze->difficulty = value_tmp;

  printf("%s\n", maze->name);
  printf("%d\n", maze->height);
  printf("%d\n", maze->width);
  printf("%d\n", maze->difficulty);

  fclose(file);
}