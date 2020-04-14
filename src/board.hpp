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
  std::string word; /*!< mot à jouer */ 
  unsigned char first_square;  /*!< case à partir de laquelle on joue */
  unsigned char j1; /*!< indice de la case où un éventuel bonus serait joué */
  unsigned char j2; /*!< indice de la case où un éventuel bonus serait joué */
  char direction; /*!< direction dans laquelle le coup est joué ('H' / 'B' / 'G' / 'D') */ 

  /**
   * @brief Constructeur par défaut
  */
  Move(){};

  /**
   * @brief Constructeur avec paramètres
   * @param _word ( \e std::string) : mot à jouer
   * @param fq ( \e unsigned \e char) : case qui contient la première lettre du mot
   * @param d ( \e unsigned \e char) : direction ('H' / 'B' / 'G' / 'D')
   * @param _j1 ( \e unsigned \e char) : position d'un éventuel 1er joker
   * @param _j2 ( \e unsigned \e char) : position d'un éventuel 2ème joker
  */
  Move(const std::string _word, const unsigned char & fq, const char & d, 
      const unsigned char & _j1 = static_cast<unsigned char>(255),
      const unsigned char & _j2 = static_cast<unsigned char>(255)) {
    word = _word;
    first_square = fq;
    direction = d;
    j1 = _j1;
    j2 = _j2;
  }

  /**
   * @fn Move& operator = (const Move& m)
   * @brief Opérateur d'affection
   * @param m ( \e Move) : coup à copier
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
   * @param copy ( \e Board&) : plateau à copier
  */
  Board(const Board& copy);



  /**************** METHODES *****************/
  
  /**
   * @fn std::pair<unsigned char,unsigned char> getIndice(const unsigned char& id) const
   * @brief Renvoie un couple de coordonnées à partir d'un indice de case
   * @param[in] id ( \e unsigned \e char) : indice de la case
   * @return \e std::pair<unsigned char, unsigned char> : paire <ligne,colonne>
  */
  std::pair<unsigned char,unsigned char> getIndice(const unsigned char& id) const;
  
  /**
   * @fn unsigned short int getIndice(const unsigned char & l,const unsigned char & c) const
   * @brief Renvoie un indice de case à partir d'un couple de coordonnées
   * @param[in] l ( \e unsigned \e char) : ligne
   * @param[in] c ( \e unsigned \e char) : colonne
   * @return \e unsigned \e short \e int : indice dans le tableau
  */
  unsigned short int getIndice(const unsigned char & l,const unsigned char & c) const;
  
  /**
   * @fn Spot* getSpot(const unsigned char & id)
   * @brief Accesseur
   * @details Renvoie la cellule pour un indice donné
   * @param[in] id ( \e unsigned \e char) : indice de la case
   * @return Spot*
  */
  Spot* getSpot(const unsigned char & id) ;

  /**
   * @fn char getLetter(const unsigned char & id) const
   * @brief Retourne la lettre contenue par une cellule
   * @param[in] id ( \e unsigned \e char) : indice de la case
   * @return char
  */
  char getLetter(const unsigned char & id) const;

  /**
   * @fn unsigned short int getWordFactor(const unsigned char & id) const
   * @brief Renvoie le word factor d'une cellule
   * @param[in] id ( \e unsigned \e char) : indice de la case
   * @return unsigned short int
  */
  unsigned short int getWordFactor(const unsigned char & id) const;

  /**
   * @fn unsigned short int getLetterFactor(const unsigned char & id) const
   * @brief Renvoie le letter factor d'une cellule
   * @param[in] id ( \e unsigned \e char) : indice de la case
   * @return unsigned short int
  */
  unsigned short int getLetterFactor(const unsigned char & id) const;

  /**
   * @fn void setLetter(const unsigned char & id, const char & c,
                  const bool & _joker = false)
   * @brief Mutateur, affecte une lettre sur une cellule
   * @param[in] id ( \e unsigned \e char) : indice de la case
   * @param[in] c ( \e char) : lettre
   * @param[in] _joker ( \e bool) : indique si la lettre jouée est un joker
  */
  void setLetter(const unsigned char & id, const char & c,
                  const bool & _joker = false);

  /**
   * @fn bool isJoker(const unsigned char & id) const
   * @brief Indique si la case contient un joker
   * @param[in] id ( \e unsigned \e char) : indice de la case dans le tableau
   * @return \e bool : \e true si la case contient un joker, \e false sinon
  */
  bool isJoker(const unsigned char & id) const;

  /**
   * @fn std::list<unsigned char> getAnchorSquares()
   * @brief Renvoie une liste qui contient les positions des anchor squares
   * @return \e std::list<unsigned char> : liste qui contient l'indice de anchor squares
  */
  std::list<unsigned char> getAnchorSquares();

  /**
   * @fn void save(std::ostream& out)
   * @brief Permet la sauvegarde d'un plateau
   * @param[out] out ( \e std::ostream&)
  */
  void save(std::ostream& out) ;

  /**
   * @fn void load (std::istream& in)
   * @brief  Permet la lecture d'un plateau
   * @param[in] in ( \e std::istream&)
  */
  void load(std::istream& in) ;

  /**
   * @fn Spot operator()(unsigned char l, unsigned char c) const
   * @brief Operator ()
   * @param[in] l ( \e unsigned \e char) : ligne
   * @param[in] c ( \e unsigned \e char) : colonne
   * @return Spot
  */
  Spot operator()(unsigned char l, unsigned char c) const ;
  
    /**
   * @fn Spot& operator()(unsigned char l, unsigned char c)
   * @brief Operator ()
   * @param[in] l ( \e unsigned \e char) : ligne
   * @param[in] c ( \e unsigned \e char) : colonne
   * @return Spot&
  */
  Spot& operator()(unsigned char l, unsigned char c) ;

  /**
   * @fn Board& operator = (const Board& b)
   * @brief Operator = d'affectation
   * @param[in] b ( \e Board) : plateau à copier
   * @return Board&
  */
  Board& operator = (const Board& b);

} ;



/**
 * @fn std::ostream& operator<<(std::ostream& out, const Board& b)
 * @brief Operateur << 
 * @details Permet l'affichage du plateau
 * @param out ( \e std::ostream)
 * @param b ( \e Board)
 * @return std::ostream
*/
std::ostream& operator<<(std::ostream& out, const Board& b) ;
