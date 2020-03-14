#pragma once

#include <list>
#include <utility>

class Node;
class Board;
class Player;
class Bag;
class Gaddag;

class Game {

public:
  Board * board;
  Player * player;
  Bag * bag;
  Gaddag * gad;


public:

  Game();

  ~Game();

  Game(const char & nb_players);

  void init();

  void printDico();

  void printHands() const;

  void printBag() const;

  void draw();

  bool isFinished() const;

  void useLetter(const std::list<unsigned int> & l);

  std::pair<unsigned short int, unsigned short int> score
                            (const unsigned char & p, const unsigned char & l) const;

  void getCrossSets(const unsigned char & square,
                    char tab_horizontal[],
                    char tab_vertical[]) const;

  void getCrossSetsHorizontal(const unsigned char & x,
                              const unsigned char & y,
                              char tab_horizontal[]) const;





};
