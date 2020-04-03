#pragma once

#include <list>


class Player {

private:
  
  //7 lettres qu'a le joueur dans sa main
  char hand[7];
  
  //liste qui indique la position de chaque lettre dans char hand[7]
  //utilisée pour exécuter des opérations en O(1)
  std::list<unsigned short int> hand_pointer[27];
  
  //points que compte le joueur
  unsigned short int points;


public:

  /**
   * @brief Constructeur par défaut, sans paramètre
  */
  Player();

  /**
   * @brief Accesseur, renvoie la lettre stockée à un indice donné
   * @param[in] \e unsigned \e short \int : indice de la case
   * @return \e char
  */
  char getLetter(const unsigned short int & n) const;

  /**
   * @brief Accesseur, renvoie l'attribut points du joueur
   * @return \e unsigned \e short \e int
  */
  unsigned short int getPoints() const;

  /**
   * @brief Mutateur, attribue une lettre au joueur
   * @param[in] \e unsigned \e short \e int  : indice de la case
   * @param[in] \e char : lettre à attriber au joueur
  */
  void setLetter(const unsigned short int n, const char & c);

  /**
   * @brief Incrémente les points du joueur
   * @param[in] \e unsigned \e short \e int : nombre de points à ajouter
  */
  void addPoints(const unsigned short int & s);

  /**
   * @brief Retire une lettre au joueur
   * @param[in] \e char
  */
  void removeLetter(const char & c);


//////// A SUPPRIMER /////////////
  void removeLetterIndice(const char & c);


  /**
   * @brief Affiche les lettres que possède le joueur 
  */ 
  void printHand() const;

};
