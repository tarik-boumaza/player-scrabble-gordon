#include "game.hpp"


Game::Game(const char & nb_players) {
  for (unsigned short int i = 0; i < nb_players; i++) {
    this->players.push_back(Player(i));
  }
}


void Game::initBag() {
  Bag b("../data/bag.txt");
  bag = b;
}


void Game::initPlayers() {
  unsigned short int i,j;
  for (i = 0; i < players.size(); i++) {
    for (j = 0; j < 7; j++)
      players[i].setLetter(j,bag.randomDraw());
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
