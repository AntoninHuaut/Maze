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

int main(void) {
  setlocale(LC_ALL, "en_US.UTF-8");
  wprintf(L"content-type:text/html; charset:utf-8\n\n");

  srand(time(NULL));
  show_menu();

  return 0;
}