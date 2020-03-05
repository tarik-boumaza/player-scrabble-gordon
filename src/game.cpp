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


void Game::printBag() const {
  bag.printLetters();
}


void Game::draw() {
  unsigned int i = 0;
  while (i < 7 && !isFinished() ) {
    if (player.getLetter(i) == '/')
      player.setLetter(i,bag.randomDraw());
    i++;
  }
}


bool Game::isFinished() const {
  return bag.isEmpty();
}


void Game::useLetter(const std::list<unsigned int> & l) {
  std::list<unsigned int> copy(l);
  while(!copy.empty()) {
    player.setLetter(copy.back(),'/');
    copy.pop_back();
  }
}
