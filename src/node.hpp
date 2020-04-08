/**
 * @file node.hpp
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

  /************************ METHODE PRIVEE ************************/

  /**
   * @fn Node* addNode(const bool & b)
   * @brief Crée et retourne un nouveau noeud
   * @param[in] b ( \e bool) : correspond à l'attribut is_final de la classe Node
   * @return *Node
  */ 
  Node* addNode(const bool & b);



public:

  /************************ CONSTRUCTEUR / DESTRUCTEUR ************************/

  /**
   * @brief Constructeur par défaut, sans paramètre
  */ 
  Node();

  /**
   * @brief Destructeur 
  */ 
  ~Node();


  /************************ METHODES PUBLIQUES ************************/

  /**
   * @fn Node* getNode(const unsigned short int & id) const
   * @brief Accesseur
   * @details Renvoie le noeud stocké à un indice donné
   * @param[in] id ( \e unsigned \e short \e int) : indice ('A'->0,..., 'Z'->25, '+'->26)
   * @return * Node
  */  
  Node* getNode(const unsigned short int & id) const;

  /**
   * @fn bool isFinal() const
   * @brief Accesseur. 
   * @details Renvoie vrai si noeud est final, faux sinon
   * @return bool : \e true si le noeud est final, \e faux
  */ 
  bool isFinal() const;

  /**
   * @fn void addNode(const std::string & word)
   * @brief Ajoute un mot au gaddag
   * @param[in] word ( \e std::string) : mot à ajouter
  */ 
  void addNode(const std::string & word);


};
