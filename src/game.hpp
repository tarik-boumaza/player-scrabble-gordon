#pragma once

#include <list>
#include <utility>


typedef std::pair<unsigned short int, unsigned short int> couple;
            ///   <case,lettre>



class Node;
class Board;
class Player;
class Bag;
class Gaddag;
struct Move;

class Game {

public:
  Board * board;
  Player * player;
  Bag * bag;
  Gaddag * gad;
  bool ended;   //signale la fin de partie : joueur bloqué ou sac vide


public:

  Game();

  ~Game();

  Game(const char & nb_players);

  Game(const Board& b);

  void draw();

  void init();

  void printDico();

  void printHand() const;

  void printBag() const;

  void print() const;

  bool isFinished() const;

  couple score (const couple & c) const;

  unsigned short int score(const std::list<couple> & l) const;

  unsigned short int score (const Board * b, const int & pos,
                            const char & direction) const;

  unsigned short int score (const Move & move) const;

  void getCrossSetsHorizontal(const unsigned char & square,
                              char tab_horizontal[], bool final, Board* b) const;

  void getCrossSetsVertical(const unsigned char & square,
                            char tab_vertical[], bool final, Board * b) const;

  //fonction qui joue un coup sur le plateau
  void makeMove(const Move & m);

  void Gen(unsigned char square,int pos, std::string& word,
          char rack[],Node* arc, unsigned int direction,
          Board * b, unsigned short int& score, Move& move);

  void GoOn(unsigned char square, int pos, char L, std::string & word,
            char rack[],Node * new_arc,Node * old_arc,
            unsigned int direction, Board * b,unsigned short int& score,
            Move& move);

  //fonction qui joue le premier coup, lorsque le plateau est vierge
  void firstMove();

  //fonction appelée à chaque tour de jeu
  void moveTurn();

  //informations de fin de partie
  void end();




};
