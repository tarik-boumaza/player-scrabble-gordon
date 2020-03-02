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


private:

  void initBag();

  void initPlayer();

  void initGaddag();



public:

  Game();

  Game(const char & nb_players);

  Player getPlayer(const unsigned int & n) const;

  void init();

  void printDico();

  void printHands() const;

  void draw();




};
