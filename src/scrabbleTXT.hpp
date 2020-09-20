/**
 * @file scrabbleTXT.hpp
*/


#pragma once


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

  /**
   * @brief Indique si le jeu se déroule en slow motion
  */
  bool sm;


public:

  /**
   * @brief Constructeur par défault
   * @param[in] _sm ( \e bool) : indique si le jeu se déroule en slow_motion
   * @param[in] _ia ( \e bool) : indique si le joueur recherche les coups intelligents
  */
  ScrabbleTXT(const bool _sm = false, const bool _ia = false);

  /**
   * @brief Destructeur
  */
  ~ScrabbleTXT();

  /**
   * @brief Fonction principale qui déroule le jeu
  */
  void play();


};
