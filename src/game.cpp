#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "bag.hpp"
#include "gaddag.hpp"
#include "game.hpp"


Game::Game() {
  bag = new Bag("./data/letters.txt","./data/points.txt");
  player = new Player;
  gad = new Gaddag;
}


void Game::init() {
  for (unsigned int i = 0;  i < 7; i++) {
    player->setLetter(i,bag->randomDraw());
  }
  gad->addDictionnary();
}


void Game::printDico() {
  gad->print();
}


void Game::printHands() const {
  player->printHand();
}


void Game::printBag() const {
  bag->printLetters();
}


void Game::draw() {
  unsigned int i = 0;
  while (i < 7 && !isFinished() ) {
    if (player->getLetter(i) == '/')
      player->setLetter(i,bag->randomDraw());
    i++;
  }
}


bool Game::isFinished() const {
  return bag->isEmpty();
}


void Game::useLetter(const std::list<unsigned int> & l) {
  std::list<unsigned int> copy(l);
  while(!copy.empty()) {
    player->setLetter(copy.back(),'/');
    copy.pop_back();
  }
}
