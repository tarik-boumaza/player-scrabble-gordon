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
  bool ended;   //signale la fin de partie : joueur bloqué


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

  bool emptyBag() const;

  couple score (const couple & c, const bool & played) const;

  unsigned short int score(const std::list<couple> & l,
                            const std::list<bool> & played) const;

  unsigned short int score (const Board * b, const int & pos,
                            const char & direction) const;

  unsigned short int score (const Move & move,
                            const unsigned char & j1 = 255,
                            const unsigned char & j2 = 255) const;

  void getCrossSetsHorizontal(const unsigned char & square,
                              char tab_horizontal[], bool final, Board* b) const;

  void getCrossSetsVertical(const unsigned char & square,
                            char tab_vertical[], bool final, Board * b) const;

  //fonction qui joue un coup sur le plateau
  void makeMove(const Move & m,
                const unsigned char & j1 = static_cast<unsigned char>(255),
                const unsigned char & j2 = static_cast<unsigned char>(255));

  void Gen(unsigned char square,int pos, std::string& word,
          char rack[],Node* arc, unsigned int direction,
          Board * b, unsigned short int& score, Move& move,
          unsigned char & j1,
          unsigned char & j2 );

  void GoOn(unsigned char square, int pos, char L, std::string & word,
            char rack[],Node * new_arc,Node * old_arc,
            unsigned int direction, Board * b,unsigned short int& score,
            Move& move, unsigned char & j1,
            unsigned char & j2);

  //fonction appelée à chaque tour de jeu
  void moveTurn();

  //informations de fin de partie
  void end();


  void attribueLettre(const std::string & s);


};
