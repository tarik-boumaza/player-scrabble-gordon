#include <iostream>
#include "game.hpp"


Game::Game() {
  this->filename = "./data/dico.txt";
}


void Game::initBag() {
  Bag b("./data/letters.txt","./data/points.txt");
  this->bag = b;
}


void Game::initPlayer() {
  unsigned short int i,j;
  char c;
  for (j = 0; j < 7; j++) {
    this->player.setLetter(j,bag.randomDraw());
  }
  std::cout << std::endl;
}


void Game::initMap() {
  node.addDictionnary(filename);
}


void Game::init() {
  initBag();
  initPlayer();
  initMap();
}


void Game::printDico() {
  node.print();
}


void Game::printHands() const {
  player.printHand();
}
