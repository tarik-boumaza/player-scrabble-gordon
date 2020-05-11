#pragma once

/**
 * @file spot.hpp
*/

#include "bonus.hpp"

#include <iostream>


/**
 * @class Spot
 * @brief Classe représentant une cellule du plateau
 */

class Spot {


private:

  char letter; /*!<lettre sur la case*/

  bool joker; /*!<indique si la lettre jouée est un joker*/
  
  Bonus bonus; /*!< bonus attribués par la case*/


/******************** CONSTRUCTEURS ******************/

public:

  /**
   * @brief Constructeur par défault
  */ 
  Spot() :
    letter(0), joker(false)
  {}

  /**
   * @brief Constructeur avec paramètres
   * @param[in] lf ( \e unsigned \e char) : letter factor
   * @param[in] wf ( \e unsigned \e char) : word factor
   * @param[in] _joker ( \e bool) : indique la lettre jouée est un joker
  */ 
  Spot(const unsigned char & lf, const unsigned char & wf,
        const bool & _joker = false) :
    letter(0), bonus(lf, wf), joker(_joker)
  {}



/******************** METHODES PUBLIQUES ******************/


  /**
   * @brief Accesseur, retourne le bonus lettre de la case
   * @return unsigned char
  */
  unsigned char getLetterFactor() const;

  /**
   * @brief Accesseur, retourne le bonus mot de la case
   * @return unsigned char
  */
  unsigned char getWordFactor() const;

  /**
   * @brief Accesseur, retourne la lettre sur la case
   * @return char
  */
  char getLetter() const;

  /**
   * @fn bool isJoker() const
   * @brief Indique si la case contient un joker
   * @return \e bool : \e true si la case contient un joker, \e false sinon
  */ 
  bool isJoker() const;

  /**
   * @fn void setLetter(const char & c, const bool & _joker = false)
   * @brief Mutateur, attribue une lettre à la case
   * @param[in] c ( \e char) : lettre à attribuer
   * @param[in] _joker ( \e bool) : indique si la lettre jouée est un joker
  */
  void setLetter(const char & c, const bool & _joker = false);

  /**
   * @brief Operateur d'affection de \e Spot
   * @param[in] s ( \e Spot) : cellule à copier
   * @return Spot& 
  */
  Spot& operator = (const Spot& s);

} ;

/**
 * @fn std::ostream& operator<<(std::ostream& out, const Spot & s)
 * @brief Operateur << pour l'affichage de la case
 * @param[in] out ( \e std::ostream&) 
 * @param[in] s ( \e Spot) : cellule à afficher
 * @return std::ostream&
*/ 
std::ostream& operator<<(std::ostream& out, const Spot & s) ;