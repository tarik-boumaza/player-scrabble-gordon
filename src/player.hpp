#pragma once

/**
 * @file player.hpp
*/

#include <list>


/**
 * @class Player
 * @brief Classe représentant un joueur
*/


class Player {

private:
  
  /**
   * @brief tableau de 7 lettres que possède le joueur
  */
  char hand[7];
  
  /**
   * @brief liste qui indique la position de chaque lettre dans char hand[7]
   * @details utilisée pour exécuter des opérations en O(1)
  */
  std::list<unsigned short int> hand_pointer[27];
  
  /** 
   * @brief points que compte le joueur
  */
  unsigned short int points;


public:

  /**
   * @brief Constructeur par défaut, sans paramètre
  */
  Player();

  /**
   * @brief Accesseur, renvoie la lettre stockée à un indice donné
   * @param[in] unsigned short int : indice de la case
   * @return char
  */
  char getLetter(const unsigned short int & n) const;

  /**
   * @brief Accesseur, renvoie l'attribut points du joueur
   * @return unsigned-short-int
  */
  unsigned short int getPoints() const;

  /**
   * @brief Mutateur, attribue une lettre au joueur
   * @param[in] unsigned-short-int  : indice de la case
   * @param[in] char : lettre à attriber au joueur
  */
  void setLetter(const unsigned short int n, const char & c);

  /**
   * @brief Incrémente les points du joueur
   * @param[in] unsigned-short-int : nombre de points à ajouter
  */
  void addPoints(const unsigned short int & s);

  /**
   * @brief Retire une lettre au joueur
   * @param[in] char
  */
  void removeLetter(const char & c);


//////// A SUPPRIMER /////////////
  void removeLetterIndice(const char & c);


  /**
   * @brief Affiche les lettres que possède le joueur 
  */ 
  void printHand() const;

};
