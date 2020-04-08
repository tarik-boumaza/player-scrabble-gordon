#pragma once

/**
 * @file scrabble.hpp
*/


class Game;


/**
 * @class ScrabbleTXT
 * @brief classe représentant le jeu de scrabble avec affichage sur la console (terminal)
*/

class ScrabbleTXT {

private:
  /**
   * @brief Pointeur sur Game
  */
  Game * g;


public:

  /**
   * @brief Constructeur par défault
  */
  ScrabbleTXT();

  /**
   * @brief Destructeur
  */
  ~ScrabbleTXT();

  /**
   * @brief Fonction principale qui déroule le jeu
   * @param[in] b ( \e bool) : est à true si le jeu est lancé au ralenti ou pas
  */
  void play(const bool & b);


};
