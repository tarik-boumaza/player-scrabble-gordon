#pragma once

#include "board.hpp"
#include "player.hpp"
#include "bag.hpp"
#include "gaddag.hpp"


class Game {

private:
  Board board;
  Player player;
  Bag bag;
  Gaddag gad;
  std::string filename;


public:

  Game();

  Game(const char & nb_players);

  Player getPlayer(const unsigned int & n) const;

  void initBag();

  void initPlayer();

  void initGaddag();

  void init();

  void printDico();

  void printHands() const;

  void draw();




};
