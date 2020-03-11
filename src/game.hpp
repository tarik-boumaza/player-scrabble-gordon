#pragma once

#include <list>
#include <utility>

class Board;
class Player;
class Bag;
class Gaddag;

class Game {

private:
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






};
