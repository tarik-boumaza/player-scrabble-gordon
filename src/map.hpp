/**
 * @file map.hpp
*/


#pragma once


#include <string>


/**
 * @class Node
 * @brief Classe représentant un noeud, donc une lettre, de la structure de gaddag
*/
class Node {

private:
  /** 
   * @brief tableau contenant tous les enfants
  */ 
  Node * tab[27]; //tab[0]->'A', ... , tab[25]->'Z', tab[26]->'+'
  
  /**
   * @brief indique si le chemin racine->noeud est un mot du dictionnaire
  */ 
  bool is_final;


private:

  /**
   * @brief Crée et retourne un nouveau noeud
   * @param[in] bool : correspond à l'attribut is_final de la classe Node
   * @return *Node
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
   * @brief Accesseur
   * @details Renvoie le noeud stocké à un indice donné
   * @param[in] unsigned-short-int : indice ('A'->0,..., 'Z'->25, '+'->26)
   * @return * Node
  */  
  Node* getNode(const unsigned short int & i) const;

  /**
   * @brief Accesseur. 
   * @details Renvoie vrai si noeud est final, faux sinon
   * @return bool 
  */ 
  bool isFinal() const;

  /**
   * @brief Ajoute un mot au gaddag
   * @param[in] std::string : mot à ajouter
  */ 
  void addNode(const std::string & s);


};
