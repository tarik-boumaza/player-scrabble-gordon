#pragma once

#include <list>
#include <string>
#include <queue>
#include <utility>


class Node;

class Gaddag {


private:

  Node * first;



private:

  /**
   * @brief Renvoie une liste contenant les mots contenant les '+' à ajouter dans le Gaddag
   * @param[in] \e std::string : mot à ajouter dans le gaddag
   * @return \e std::list<std::string> : liste de mots
  */ 
  std::list<std::string> mirror(const std::string & word) ;

  /**
   * @brief Fonction récursive d'affichage du gaddag
   * @param[in-out] * \e Node , \e std::list<std::pair<char,Node*>> , \e char
  */  
  void print_letters(Node* node,
                    std::list<std::pair<char,Node*>> & l,
                    const char & c);

public:

  /**
   * @brief Constructeur par défaut
  */ 
  Gaddag();

  /**
   * @brief Destructeur
  */
  ~Gaddag();

  /**
   * @brief Renvoie la lettre correspondant à un indice donné
   * @param[in] \e unsigned \e short \e int 
   * @return \e char
  */  
  char getLetter(const unsigned short int & n) const;

  /**
   * @brief Ajoute un mot avec l'insertion de '+' dans la Gaddag
   * @param[in] \e std::string 
  */ 
  void addNodePlus(const std::string & s);

  /**
   * @brief Ajoute l'ensemble du dictionnaire au Gaddag
  */ 
  void addDictionnary();

  /**
   * @brief Affiche l'ensemble des mots contenus dans le Gaddag
  */ 
  void print();

  /**
   * @brief Accesseur, renvoie le noeud racine du gaddag
   * @return * \e Node
  */ 
  Node* getFirst();



};
