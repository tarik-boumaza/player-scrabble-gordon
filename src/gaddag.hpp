/**
 * @file gaddag.hpp
*/


#pragma once


#include <list>
#include <string>
#include <queue>
#include <utility>


class Node;


/**
 * @class Gaddag
 * @brief Classe représentant la structure de gaddag
*/

class Gaddag {


private:
  
  /**
   * @brief Racine du gaddag
  */
  Node * first; 



  /************************ METHODES PRIVEES ************************/

private:

  /**
   * @fn void print_letters(Node* node, std::list<std::pair<char,Node*>> & l, const char & c)
   * @brief Fonction récursive d'affichage du gaddag
   * @param[in-out] node ( \e *Node) 
   * @param[in-out] l ( \e std::list<std::pair<char,Node*>>)
   * @param[in] c ( \e char)
  */  
  void print_letters(Node* node,
                    std::list<std::pair<char,Node*>> & l,
                    const char & c);



public:

  /************************ CONSTRUCTEUR/DESTRUCTEUR ************************/

  /**
   * @brief Constructeur par défaut
  */ 
  Gaddag();

  /**
   * @brief Destructeur
  */
  ~Gaddag();



  /************************ METHODES ************************/


  /**
   * @fn char getLetter(const unsigned short int & n) const
   * @brief Renvoie la lettre correspondant à un indice donné
   * @param[in] n ( \e unsigned \e short \e int) : indice 
   * @return char
  */  
  char getLetter(const unsigned short int & n) const;

  /**
   * @fn void addNodePlus(const std::string & word)
   * @brief Ajoute un mot avec l'insertion de '+' dans la Gaddag
   * @param[in] word ( \e std::string) mot à ajouter
  */ 
  void addNodePlus(const std::string & word);

  /**
   * @fn void addDictionnary()
   * @brief Ajoute l'ensemble du dictionnaire au Gaddag
  */ 
  void addDictionnary();

  /**
   * @fn void print()
   * @brief Affiche l'ensemble des mots contenus dans le Gaddag
  */ 
  void print();

  /**
   * @fn Node* getFirst()
   * @brief Accesseur, renvoie le noeud racine du gaddag
   * @return *Node
  */ 
  Node* getFirst();


};



/**
  * @fn std::list<std::string> mirror(const std::string & word)
  * @brief Renvoie une liste contenant les mots contenant les '+' à ajouter dans le Gaddag
  * @param[in] word (\e std::string) : mot à ajouter dans le gaddag
  * @return std::list<std::string> : liste de mots
*/ 