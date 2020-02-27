#pragma once

#include "board.hpp"
#include "player.hpp"
#include "bag.hpp"
#include "map.hpp"


class Game {

private:
  Board board;
  Player player;
  Bag bag;
  Node node;
  std::string filename;


public:

  Game();

  Game(const char & nb_players);

  Player getPlayer(const unsigned int & n) const;

  void initBag();

  void initPlayer();

  void initMap();

  void init();

  void printDico();

  void printHands() const;




};
