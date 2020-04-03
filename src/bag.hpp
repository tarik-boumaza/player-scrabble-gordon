#pragma once

/**
 * @file bag.hpp
*/

#include <string>



/**
 * @class Bag
 * @brief Classe représentant le sac de lettre
*/

class Bag {

private:

  /** 
   * @brief nombre de points rapportés par une lettre
  */
  unsigned int points[27]; //points[26] pour le Joker 
  
  /** 
   * @brief tableau de caractères qui contient toutes les lettres du sac
  */
  char letters[104]; //seules les premières nb_letters sont remplies
  
  /**
   * @brief nombre de lettres présentes dans le sac
  */
  unsigned int nb_letters;



public:

  /**
   * @brief Constructeur
   * @param[in] std::string : chemin vers le fichier qui contient les lettres 
   * l'attribut file_l doit être exact et fourni avec l'extension \file fichier.txt
   * @param[in] std::string : chemin vers le fichier qui contient les points
   * l'attribut file_p doit être exact et fourni avec l'extension \file fichier.txt
  */
  Bag(const std::string & file_l, const std::string & file_p);


  /**
   * @brief Accesseur
   * @param[in] char : indice de la case ou lettre
   * @return unsigned short int
  */
  unsigned short int getPoints(const unsigned char & c) const;

  /**
   * @brief Teste si le sac est vide
   * @return bool 
  */
  bool isEmpty() const;

  /**
   * @brief Effectue un tirage aléatoire dans le sac
   * @details complexité : O(1)
   * @return char
  */
  char randomDraw();

  /** 
   * @brief Affiche les lettres présentes dans le sac
  */
  void printLetters() const;

  /**
   * @brief Affiche les lettres présentes dans le sac
  */
  void printPoints() const;



};
