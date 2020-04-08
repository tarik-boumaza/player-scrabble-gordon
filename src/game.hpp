/**
 * @file game.hpp
*/


#pragma once


#include <list>
#include <utility>


class Node;
class Board;
class Player;
class Bag;
class Gaddag;
struct Move;



/**
 * typedef qui représente une association <case, lettre> 
*/ 
typedef std::pair<unsigned short int, unsigned short int> couple;


class Game {

private:

  Board * board; /*!< plateau du jeu */
  Player * player; /*!< joueur */
  Bag * bag; /*!< sac de lettre */
  Gaddag * gad; /*!< structure de gaddag */
  bool ended;  /*!< signale la fin de partie (joueur bloqué) */ 


public:

  /****************** CONSTRUCTEURS / DESTRUCTEUR ******************/

  Game();

  Game(const char & nb_players);

  Game(const Board& b);

  ~Game();



  /****************** METHODES PRIVEES ******************/


private :


  void printDico();

  void printHand() const;

  void printBag() const;

  void draw();

  couple score (const couple & c, const bool & played) const;

  /**
   * @fn unsigned short int score(const std::list<couple> & l,
                            const std::list<bool> & played) const
   * @brief Calcule le score
   * @param[in] l ( \e std::list<couple>) : liste qui contient des \e couple
   * @param[in] played ( \e std::list<bool>) : liste qui contient des booléens : \e true si la case contient déjà la lettre, \e false sinon
   * @return unsigned short int
  */ 
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
  void makeMove(const Move & m);

  void Gen(unsigned char square,int pos, std::string& word,
          char rack[],Node* arc, unsigned char direction,
          Board * b, unsigned short int& score, Move& move,
          unsigned char & j1,
          unsigned char & j2 );

  void GoOn(unsigned char square, int pos, char L, std::string & word,
            char rack[],Node * new_arc,Node * old_arc,
            unsigned char direction, Board * b,unsigned short int& score,
            Move& move, unsigned char & j1,
            unsigned char & j2);




  /****************** METHODES PUBLIQUES ******************/


public :

  void init();

  void print() const;

  bool isFinished() const;

  bool emptyBag() const;

  //fonction appelée à chaque tour de jeu
  void moveTurn();

  //informations de fin de partie
  void end();








  void attribueLettre(const std::string & s);


};
