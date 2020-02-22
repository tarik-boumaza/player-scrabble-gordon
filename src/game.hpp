#pragma once

#include <vector>
#include "board.hpp"
#include "player.hpp"
#include "sac.hpp"
#include "map.hpp"


class Game {

private:
  Board board;
  std::vector<Player> players;
  Bag bag;
  Noeud node;


public:

  Game(const char & nb_players);

  void initBag();

  void initPlayers();

  void initMap();

  void init();




};
