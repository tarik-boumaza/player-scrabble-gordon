#pragma once

#include <string>

class Node {

private:
  //tableau contenant tous les enfants
  Node * tab[27]; //tab[0]->'A', ... , tab[25]->'Z', tab[26]->'+'
  //indique si le chemin racine->noeud est un mot du dictionnaire
  bool is_final;


private:

  /**
   * @brief 
   * @param[in] \e bool : correspond à l'attribut is_final de la classe \e Node
   * @return * \e Node
  */ 
  Node* addNode(const bool & b);


public:
  /**
   * @brief Constructeur par défaut, sans paramètre
  */ 
  Node();

  /**
   * @brief Destructeur 
  */ 
  ~Node();

  /**
   * @brief Accesseur, renvoie le noeud stocké à un indice donné
   * @param[in] \e unsigned \e short \e int
   * @return * \e Node
  */  
  Node* getNode(const unsigned short int & i) const;

  /**
   * @brief Accesseur. Renvoie vrai si noeud est final, faux sinon
   * @return \e bool 
  */ 
  bool isFinal() const;

  /**
   * @brief Ajoute un mot au gaddag
   * @param[in] \e std::string : mot à ajouter
  */ 
  void addNode(const std::string & s);


};
