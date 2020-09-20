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

  float weights1[27]; /*!<poids 1 pour le calcul de la valeur du rack*/

  float weights2[27]; /*!<poids 2 pour le calcul de la valeur du rack*/

  float vc_ratio[28]; /*!<ratio voyelles/consonnes pour calcul de valeur du rack*/

  unsigned int nb_letters; /*!<nombre de lettres présentes dans le sac*/




public:

  /**
   * @brief Constructeur
   * @param[in] filename_l ( \e std::string) : chemin vers le fichier qui contient les lettres
   * @param[in] filename_p ( \e std::string) : chemin vers le fichier qui contient les points
   * @param[in] filename_w1 ( \e std::string) : chemin vers le fichier qui contient les poids 1 des lettres
   * @param[in] filename_w2 ( \e std::string) : chemin vers le fichier qui contient les poids 2 des lettres
   * @param[in] filename_vc ( \e std::string) : chemin vers le fichier qui contient le ration voyelles/consonnes
   * les attributs filename_X doivent être exacts et fournis avec l'extension 'fichier.txt'
  */
  Bag(const std::string & filename_l = "./data/letters.txt",
      const std::string & filename_p = "./data/points.txt",
      const std::string & filename_w1 = "./data/weights1.txt",
      const std::string & filename_w2 = "./data/weights2.txt",
      const std::string & filename_vc = "./data/vowels_consonants.txt");



  /**************** METHODES *****************/


  /**
   * @fn unsigned short int getPoints(const unsigned char & id) const
   * @brief Accesseur
   * @param[in] id ( \e unsigned \e char) : indice de la case ou lettre
   * @return \e unsigned \e short \e int : nombre de points rapportés par une lettre
  */
  unsigned short int getPoints(const unsigned char & id) const;

  /**
   * @fn float getWeight1(const char & letter) const
   * @brief Accesseur
   * @param[in] letter ( \e char) : lettre dont on veut retourner le poids 1
   * @return \e float : poids de la lettre
  */
  float getWeight1(const char & letter) const;

  /**
   * @fn float getWeight2(const char & letter) const
   * @brief Accesseur
   * @param[in] letter ( \e char) : lettre dont on veut retourner le poids 2
   * @return \e float : poids de la lettre
  */
  float getWeight2(const char & letter) const;

  /**
   * @fn float getRatio(const int & nb_vowels,
               const int & nb_consonants) const;
   * @brief Accesseur
   * @param[in] nb_vowels ( \e int) : nombre de voyelles
   * @param[in] nb_consonants ( \e int) : nombre de consonnes
   * @return \e float : rapport voyelles/consonnes
  */
  float getRatio(const int & nb_vowels,
               const int & nb_consonants) const;

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


};
