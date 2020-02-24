#pragma once

#include <vector>
#include "board.hpp"
#include "player.hpp"
#include "bag.hpp"
#include "map.hpp"


class Game {

private:
  Board board;
  std::vector<Player> players;
  Bag bag;
  Noeud node;
  std::string filename;


public:

  Game();

  Game(const char & nb_players);

  Player getPlayer(const unsigned int & n) const;

  void initBag();

  void initPlayers();

  void initMap();

  void init();

  void printDico();

  void printHands() const;




};
