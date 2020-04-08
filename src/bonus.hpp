/**
 * @file bonus.hpp
*/

#pragma once


/**
 * @class Bonus
 * @brief Classe permettant d'attribuer des bonus à des cases du plateau
*/
class Bonus {

public:
  
  /**
   * @brief Constructeur par défaut
   * @details Bonus par défauts : facteur 1 pour lettre et pour mot
  */
  Bonus() :
    letter_factor(1), word_factor(1)
  {}

  /**
   * @brief Constructeur avec initialisation des facteurs
   * @param[in] lf : facteur lettre
   * @param[in] wf : facteur mot
  */
  Bonus(unsigned char lf, unsigned char wf) :
    letter_factor(lf), word_factor(wf)
  {}

  /**
   * @fn unsigned char getLetterFactor() const
   * @brief Accesseur
   * @details Renvoie le facteur lettre
  */
  unsigned char getLetterFactor() const;

  /**
   * @fn unsigned char getWordFactor() const
   * @brief Accesseur
   * @details Renvoie le facteur mot
  */
  unsigned char getWordFactor() const;

  /**
   * @fn Bonus& operator = (const Bonus & b)
   * @brief Operateur d'affectation
   * @param[in] b \e Bonus
   * @return Bonus&
  */
  Bonus& operator = (const Bonus & b);

private:

  unsigned char letter_factor ;
  unsigned char word_factor ;

} ;
