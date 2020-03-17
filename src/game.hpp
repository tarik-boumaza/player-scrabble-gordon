#pragma once

#include <list>
#include <utility>

typedef std::pair<unsigned short int, unsigned short int> couple;


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

  void draw(const unsigned short int & n = 1);

  void init();

  void printDico();

  void printHand() const;

  void printBag() const;

  bool isFinished() const;

  void useLetter(const char & c);

  couple score (const couple & c) const;

  unsigned short int score(const std::list<couple> & l) const;

  void getCrossSetsHorizontal(const unsigned char & square, char tab_horizontal[]);

  void getCrossSetsVertical(const unsigned char & square, char tab_horizontal[]);





};
