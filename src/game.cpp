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
  for (unsigned int i = 0;  i < 7; i++) {
    player.setLetter(i,bag.randomDraw());
  }
}


void Game::initGaddag() {
  gad.addDictionnary(filename);
}


void Game::init() {
  initBag();
  initPlayer();
  initGaddag();
}


void Game::printDico() {
  gad.print();
}


void Game::printHands() const {
  player.printHand();
}


void Game::draw() {
  unsigned int i = 0;
  while (i < 7 && !bag.isEmpty() ) {
    if (player.getLetter(i) == '/')
      player.setLetter(i,bag.randomDraw());
  }
}
