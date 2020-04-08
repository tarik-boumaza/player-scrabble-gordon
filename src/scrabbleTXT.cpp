/**
 * @file scrabbleTXT.cpp
*/


#include <iostream>
#include <unistd.h>
#include "game.hpp"
#include "scrabbleTXT.hpp"


ScrabbleTXT::ScrabbleTXT() {
  g = new Game;
  g->init();
}


ScrabbleTXT::~ScrabbleTXT() {
  delete g;
}


static void clean() {
  int * n = new int;
  *n = system("clear");
  delete n;
}


void ScrabbleTXT::play(const bool & b) {
  clean();
  g->print();
  unsigned short int i = 1;
  while (!g->isFinished()) {
    //clean();
    std::cout << "Coup n° " << i << std::endl << std::endl;
    g->moveTurn();
    g->print();
    i++;
    if (b)
      usleep(1500000);
  }
  g->print();
  g->end();
}
