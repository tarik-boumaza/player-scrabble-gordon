/**
 * @file player.hpp
*/


#pragma once


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

  /************************ CONSTRUCTEUR ************************/

  /**
   * @brief Constructeur par défaut, sans paramètre
  */
  Player();


  /************************ METHODES ************************/

  /**
   * @brief Accesseur
   * @details Renvoie la lettre stockée à un indice donné
   * @param[in] n (\e unsigned \e short \e int) : indice de la case
   * @return char
  */
  char getLetter(const unsigned short int & n) const;

  /**
   * @brief Accesseur, renvoie l'attribut points du joueur
   * @return unsigned short int
  */
  unsigned short int getPoints() const;

  /**
   * @brief Mutateur, attribue une lettre au joueur
   * @param[in] n ( \e unsigned \e short \e int) : indice de la case
   * @param[in] c ( \e char) : lettre à attribuer au joueur
  */
  void setLetter(const unsigned short int n, const char & c);

  /**
   * @brief Incrémente les points du joueur
   * @param[in] pts ( \e unsigned \e short \e int) : nombre de points à ajouter
  */
  void addPoints(const unsigned short int & pts);

  /**
   * @brief Retire une lettre au joueur
   * @param[in] c ( \e char) : lettre à retirer
   * @return unsigned short int
  */
  unsigned short int removeLetter(const char & c);


//////// !!!!!!!!!!!!!!!!!!!!!!A SUPPRIMER !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! /////////////
  void removeLetterIndice(const char & c);


  /**
   * @brief Affiche les lettres que possède le joueur 
  */ 
  void printHand() const;

};
