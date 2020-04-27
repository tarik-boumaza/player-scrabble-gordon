/**
 * @file bag.hpp
*/

#pragma once


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
  unsigned int points[27]; // points[26] pour le Joker
  
  /** 
   * @brief tableau de caractères qui contient toutes les lettres du sac
  */
  char letters[104]; //seules les premières nb_letters sont remplies
  
  float weights1[27]; 

  float weights2[27]; 

  unsigned int nb_letters; /*!<nombre de lettres présentes dans le sac*/




public:

  /**
   * @brief Constructeur
   * @param[in] file_l ( \e std::string) : chemin vers le fichier qui contient les lettres 
   * l'attribut file_l doit être exact et fourni avec l'extension 'fichier.txt'
   * @param[in] file_p ( \e std::string) : chemin vers le fichier qui contient les points
   * l'attribut file_p doit être exact et fourni avec l'extension 'fichier.txt'
  */
  Bag(const std::string & file_l = "./data/letters.txt",
      const std::string & file_p = "./data/points.txt",
      const std::string & filename_w1 = "./data/weights1.txt",
      const std::string & filename_w2 = "./data/weights2.txt");



  /**************** METHODES *****************/


  /**
   * @fn unsigned short int getPoints(const unsigned char & id) const
   * @brief Accesseur
   * @param[in] id ( \e unsigned \e char) : indice de la case ou lettre
   * @return \e unsigned \e short \e int : nombre de points rapportés par une lettre
  */
  unsigned short int getPoints(const unsigned char & id) const;

  /**
   * @fn bool isEmpty()
   * @brief Teste si le sac est vide
   * @return \e bool : \e true si le sac est vide, \e false sinon 
  */
  bool isEmpty() const;

  /**
   * @fn char randomDraw()
   * @brief Effectue un tirage aléatoire dans le sac
   * @details complexité : O(1)
   * @return \e char : lettre tirée aléatoirement
  */
  char randomDraw();

  /** 
   * @fn void printLetters() const
   * @brief Affiche les lettres présentes dans le sac
  */
  void printLetters() const;

  /**
   * @fn void printPoints() const
   * @brief Affiche les lettres présentes dans le sac
  */
  void printPoints() const;


  void printWeights() const;



};
