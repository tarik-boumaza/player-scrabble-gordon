/**
 * @file board.hpp
*/


#pragma once


#include "spot.hpp"
#include <iostream>
#include <list>


/**
 * @struct Move
 * @brief Structure définissant un coup joué sur le plateau
*/

struct Move{
  std::string word;
  unsigned char first_square;
  unsigned char j1;
  unsigned char j2;
  char direction;

  /**
   * @brief Constructeur par défaut
  */
  Move(){};

  /**
   * @brief Constructeur avec paramètres
   * @param std::string : mot à jouer
   * @param unsigned char : case qui contient la première lettre du mot
   * @param unsigned char : direction ('H' / 'B' / 'G' / 'D')
   * @param unsigned char : position d'un éventuel 1er joker
   * @param unsigned char : position d'un éventuel 2ème joker
  */
  Move(const std::string w, const unsigned char & fq,
      const char & d, const unsigned char & _j1,
      const unsigned char & _j2) {
    word = w;
    first_square = fq;
    direction = d;
    j1 = _j1;
    j2 = _j2;
  }

  /**
   * @brief Opérateur d'affection
   * @param Move
   * @return Move&
  */
  Move& operator = (const Move& m){
    word = m.word;
    first_square = m.first_square;
    direction = m.direction;
    j1 = m.j1;
    j2 = m.j2;
  }

};



/**
 * @class Board
 * @brief Classe définissant un plateau
 * @details Composée d'un tableau de 225 cellules (cf classe Spot)
*/

class Board {

private:
  Spot spots[225] ; /*!<  Tableau des 225 cellules (cf classe Spot) qui composent le plateau */


public:

  /**************** CONSTRUCTEURS *****************/

  /**
   * @brief Constructeur par défaut
  */
  Board() ;

  /**
   * @brief Constructeur par copie
   * @param Board&
  */
  Board(const Board& copy);



  /**************** METHODES *****************/
  
  /**
   * @fn std::pair<unsigned char,unsigned char> getIndice(const unsigned char& n)
   * @brief Renvoie un couple de coordonnées à partir d'un indice de case
   * @param[in] unsigned char
   * @return std::pair<unsigned char, unsigned char>
  */
  std::pair<unsigned char,unsigned char> getIndice(const unsigned char& n);
  
  /**
   * @fn unsigned short int getIndice(const unsigned char & x,const unsigned char &y)
   * @brief Renvoie un indice de case à partir d'un couple de coordonnées
   * @param[in] unsigned char : ligne
   * @param[in] unsigned char : colonne
   * @return unsigned short int
  */
  unsigned short int getIndice(const unsigned char & x,const unsigned char &y);
  
  /**
   * @fn Spot* getSpot(const unsigned char & i)
   * @brief Accesseur
   * @details Renvoie la cellule pour un indice donné
   * @param[in] unsigned char : indice de la case
   * @return Spot*
  */
  Spot* getSpot(const unsigned char & i);

  /**
   * @fn char getLetter(const unsigned char & i) const
   * @brief Retourne la lettre contenue par une cellule
   * @param[in] unsigned char : indice de la case
   * @return char
  */
  char getLetter(const unsigned char & i) const;

  /**
   * @fn unsigned short int getWordFactor(const unsigned char & id) const
   * @brief Renvoie le word factor d'une cellule
   * @param[in] unsigned char : indice de la case
   * @return unsigned short int
  */
  unsigned short int getWordFactor(const unsigned char & id) const;

  /**
   * @fn unsigned short int getLetterFactor(const unsigned char & id) const
   * @brief Renvoie le letter factor d'une cellule
   * @param[in] unsigned char : indice de la case
   * @return unsigned short int
  */
  unsigned short int getLetterFactor(const unsigned char & id) const;

  /**
   * @fn void setLetter(const unsigned char & n, const char & c)
   * @brief Mutateur, pose une lettre sur une cellule
   * @param[in] unsigned char : indice de la case
   * @param[in] char : lettre
  */
  void setLetter(const unsigned char & n, const char & c);

  /**
   * @fn std::list<unsigned char> getAnchorSquares()
   * @brief Renvoie une liste qui contient les positions des anchor squares
   * @return std::list<unsigned char>
  */
  std::list<unsigned char> getAnchorSquares();

  /**
   * @fn void save(std::ostream& out)
   * @brief Permet la sauvegarde d'un plateau
   * @param[out] std::ostream&
  */
  void save(std::ostream& out) ;

  /**
   * @fn void load (std::istream& in)
   * @brief  Permet la lecture d'un plateau
   * @param[in] std::istream&
  */
  void load(std::istream& in) ;

  /**
   * @fn Spot operator()(unsigned char l, unsigned char c) const
   * @brief Operator ()
   * @param[in] unsigned char : ligne
   * @param[in] unsigned char : colonne
   * @return Spot
  */
  Spot operator()(unsigned char l, unsigned char c) const ;
  
    /**
   * @fn Spot& operator()(unsigned char l, unsigned char c) const
   * @brief Operator ()
   * @param[in] unsigned char : ligne
   * @param[in] unsigned char : colonne
   * @return Spot&
  */
  Spot& operator()(unsigned char l, unsigned char c) ;

  /**
   * @fn Board& operator = (const Board& b)
   * @brief Operator = d'affectation
   * @param[in] Board
   * @return Board&
  */
  Board& operator = (const Board& b);

} ;



/**
 * @fn
 * @brief Operateur << 
 * @details Permet l'affichage du plateau
 * @param std::ostream
 * @param Board
 * @return std::ostream
*/
std::ostream& operator<<(std::ostream& out, const Board& b) ;
