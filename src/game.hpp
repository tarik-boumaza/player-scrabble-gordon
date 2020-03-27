#pragma once

#include <list>
#include <utility>

// first -> indice de la case, second -> la lettre que contient la case
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

  Game(const Board& b);

  void draw(const unsigned short int & n = 1);

  void init();

  void printDico();

  void printHand() const;

  void printBag() const;

  bool isFinished() const;

  void useLetter(const char & c);

  couple score (const couple & c) const;

  unsigned short int score(const std::list<couple> & l) const;

  void getCrossSetsHorizontal(const unsigned char & square, char tab_horizontal[], bool final);

  void getCrossSetsVertical(const unsigned char & square, char tab_vertical[], bool final);

  void Gen(unsigned char  square,int pos, std::string& word,unsigned int rack[],Node* arc, unsigned int direction, Board* b, unsigned short int& score, Move& move);

  void GoOn(unsigned char  square, int pos, char L, std::string & word, unsigned int rack[],Node* new_arc,Node* old_arc, unsigned int direction, Board* b,unsigned short int& score, Move& move);





};
