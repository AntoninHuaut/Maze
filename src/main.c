#include "../header/main.h"

void init_game() {
  maze_ maze;
  int index;
  char default_name[NAME_MAZE_LENGTH] = DEFAULT_MAZE_NAME;

  for (index = 0; index < NAME_MAZE_LENGTH; index++) {
    maze.name[index] = default_name[index];
  }

  maze.height = DEFAULT_SIZE_HEIGHT;
  maze.width = DEFAULT_SIZE_WIDTH;
  show_menu(maze);
}

int main(void) {
  srand(time(NULL));
  init_game();

  return 0;
}