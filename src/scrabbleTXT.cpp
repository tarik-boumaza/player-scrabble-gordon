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


void ScrabbleTXT::play() {
  unsigned short int i = 1;
  clean();
  std::cout << "Coup n° " << i << std::endl << std::endl;
  //g->firstMove();  //premier coup, lorsque le plateau est vierge
  g->print();
  usleep(1500000);
  while (!g->isFinished()) {
    i++;
    //g->moveTurn();
    clean();
    std::cout << "Coup n° " << i << std::endl << std::endl;
    g->print();
    usleep(1500000);
    g->draw();
  }
  g->end();
}
