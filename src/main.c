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
#include "../header/main.h"

MU_TEST(test_check) {
  mu_check(5 == 7);
}

MU_TEST_SUITE(test_maze) {
  MU_RUN_TEST(test_check);
}

void run_tests() {
  MU_RUN_SUITE(test_maze);
  MU_REPORT();
}

int main(void) {
  srand(time(NULL));
  setlocale(LC_ALL, "");

#ifdef UNIT_TESTS
  run_tests();
  return MU_EXIT_CODE;
#else
  show_menu();
  return 0;
#endif
}