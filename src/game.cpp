#include <iostream>
#include "game.hpp"


Game::Game() {
  this->players.push_back(Player(1));
}


Game::Game(const char & nb_players) {
  for (unsigned short int i = 0; i < nb_players; i++) {
    this->players.push_back(Player(i));
  }
}


Player Game::getPlayer(const unsigned int & n) const {
  try {
    if (n < players.size())
      throw "Attention, case non déclarée";
    else
      return players[n];
  }
  catch (const std::string & s) {
    std::cerr << s;
  }
  Player p(0);
  return p;
}


void Game::initBag() {
  Bag b("../data/bag.txt");
  //bag = b;
}


void Game::initPlayers() {
  unsigned short int i,j;
  char c;
  for (i = 0; i < players.size(); i++) {
    for (j = 0; j < 7; j++) {
      c = bag.randomDraw();
      players[i].setLetter(j,c);
    }
    std::cout << std::endl;
  }
}


void Game::initMap() {
  //node.addDictionnary();
}


void Game::init() {
  initBag();
  initPlayers();
  initMap();
}
