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
  /**
   * @brief Lettre sur la case
  */
  char letter;
  
  /**
   * @brief Bonus de la case
  */
  Bonus bonus;


public:

  /**
   * @brief Constructeur par défault
  */ 
  Spot() :
    letter(0)
  {}

  /**
   * @brief Constructeur avec paramètres
   * @param[in] lf ( \e unsigned \e char) : letter factor
   * @param[in] wf ( \e unsigned \e char) : word factor
  */ 
  Spot(unsigned char lf, unsigned char wf) :
    letter(0), bonus(lf, wf)
  {}

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
   * @brief Mutateur, attribue une lettre à la case
   * @param[in] c ( \e char) : lettre à attribuer
  */
  void setLetter(const char & c);

  /**
   * @brief Operateur d'affection de \e Spot
   * @param[in] s ( \e Spot) : cellule à copier
   * @return Spot& 
  */
  Spot& operator = (const Spot& s);

} ;

/**
 * @brief Operateur << pour l'affichage de la case
 * @param[in-out] out ( \e std::ostream&) 
 * @param[in] s ( \e Spot) : cellule à afficher
 * @return std::ostream&
*/ 
std::ostream& operator<<(std::ostream& out, const Spot & s) ;
