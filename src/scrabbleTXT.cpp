/**
 * @file scrabbleTXT.cpp
*/


#include "game.hpp"
#include "scrabbleTXT.hpp"
#include <iostream>
#include <unistd.h>


ScrabbleTXT::ScrabbleTXT(const bool _sm, const bool _ia) {
  sm = _sm;
  g = new Game(_ia);
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


void ScrabbleTXT::play() {
  clean();
  g->print();
  unsigned short int i = 1;
  while (!g->isFinished()) {
    std::cout << "Coup n° " << i << std::endl << std::endl;
    g->moveTurn();
    g->print();
    i++;
    if (sm)    /// jeu en slow motion
      usleep(1500000);
  }
  g->print();
  g->finalPrint();
}
