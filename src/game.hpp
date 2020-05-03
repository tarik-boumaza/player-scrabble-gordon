/**
 * @file game.hpp
*/


#pragma once

#include <string>
#include <list>
#include <utility>


class Node;
struct Move;
class Board;
class Player;
class Bag;
class Gaddag;



/**
 * typedef qui représente une association <cellule, lettre>
*/
typedef std::pair<unsigned short int, unsigned short int> couple;


/**
 * @class Game
 * @brief Classe représentant le jeu de scrabble
*/
class Game {

public:

  Board * board; /*!< plateau du jeu */
  Player * player; /*!< joueur */
  Bag * bag; /*!< sac de lettre */
  Gaddag * gad; /*!< structure de gaddag */
  bool ended;  /*!< signale la fin de partie (joueur bloqué) */


public:

  /****************** CONSTRUCTEUR / DESTRUCTEUR ******************/

  /**
   * @brief Constructeur par défaut, sans paramètre
  */
  Game();

  /**
   * @brief Destructeur
  */
  ~Game();



  /****************** METHODES PRIVEES ******************/


public:

  /**
   * @fn void printDico() const
   * @brief Affiche l'intégralité des mots contenus dans le gaddag
  */
  void printDico() const;

  /**
   * @fn void printHand() const
   * @brief Affiche les lettres que possède le joueur
  */
  void printHand() const;

  /**
   * @fn void printBag() const
   * @brief Affichage le contenu du sac
  */
  void printBag() const;

  /**
   * @fn void draw(const char & letter)
   * @brief Tirage aléatoire des lettres
   * @details Remplace une lettre jouée en attribuant au joueur une lettre aléatoirement tirée parmi les lettres restantes dans le sac
   * Complexité : O(1)
   * @param[in] letter ( \e char) : lettre à remplacer
  */
  void draw(const char & letter);

  /**
   * @fn couple score (const couple & c, const bool & played) const
   * @brief Calcule le score
   * @param[in] c ( \e couple) : association <cellule, lettre>
   * @param[in] played ( \e bool) : \e true si la lettre est posée par le joueur, \e false sinon
   * @return \e couple : paire <score, facteur mot>
  */
  couple score (const couple & c, const bool & played) const;

  /**
   * @fn unsigned short int score(const std::list<couple> & l,
                            const std::list<bool> & played) const
   * @brief Calcule le score
   * @param[in] l ( \e std::list<couple>) : liste qui contient des \e couple
   * @param[in] played ( \e std::list<bool>) : liste qui contient des booléens : \e true si la case contient déjà la lettre, \e false sinon
   * @return \e unsigned \e short \e int : points rapportés
  */
  unsigned short int score(const std::list<couple> & l,
                            const std::list<bool> & played) const;

  /**
   * @fn unsigned short int score (const Board * b, const int & pos,
                            const char & direction) const
   * @brief Calcule le score
   * @details Cas où on complète un autre mot
   * @param[in] b (* \e Board)
   * @param[in] pos ( \e int) : indice de la case à  partir de laquelle on calcule le score
   * @param[in] direction ( \e char) : direction vers laquelle le mot est joué
   * @return \e unsigned \e short \e int : points rapporté par le coup
  */
  unsigned short int score (const Board * b, const int & pos,
                            const char & direction) const;

  /**
   * @fn unsigned short int bonusScore(const unsigned char & pos,
                                const unsigned char & board_pos,
                                const char & temp_word,
                                const char & direction) const
   * @brief Calcule le score
   * @details Cas où le joueur complète un autre mot, organise l'appel à la fonction ci-dessus)
   * @param[in] board_pos ( \e unsigned \e char) : position à partir de laquelle se joue le mot
   * @param[in] temp_word ( \e char) : lettre qui complète le mot
   * @param[in] direction ( \e char) : direction vers laquelle se trouve le mot complété
   * @return \e unsigned \e short \e int : points rapportés
  */
  unsigned short int bonusScore(const unsigned char & board_pos,
                                const char & temp_word,
                                const char & direction) const;

  /**
   * @fn unsigned short int score (const Move & move) const
   * @brief Calcule le score
   * @param[in] move ( \e Move) : coup joué
   * @return \e unsigned \e short \e int : points rapporté par le coup
  */
  unsigned short int score (const Move & move) const;

  float grade(const char rack[]) const;

  /**
   * @fn void getCrossSetsHorizontal(const unsigned char & square,
                              char tab_horizontal[], bool final,
                              Board* b) const
   * @brief Retourne l'ensemble des lettres jouable à partir d'une case horizontalement
   * @param[in] square ( \e unsigned \e char) : case courante
   * @param[out] tab_horizontal ( \e char[]) : les lettres jouables à partir ce cette case
   * @param[in] final ( \e bool) : indique si les lettres recherchées doivent être finales
   * @param[in] b ( \e Board*) : plateau utilisé pour la recherche des lettres
  */
  void getCrossSetsHorizontal(const unsigned char & square,
                              char tab_horizontal[], bool final,
                              Board* b) const;

  /**
  * @fn void getCrossSetsVertical(const unsigned char & square,
                             char tab_vertical[], bool final,
                             Board* b) const
  * @brief Retourne l'ensemble des lettres jouable à partir d'une case verticalement
  * @param[in] square ( \e unsigned \e char) : case courante
  * @param[out] tab_vertical ( \e char[]) : les lettres jouables à partir ce cette case
  * @param[in] final ( \e bool) : indique si les lettres recherchées doivent être finales
  * @param[in] b ( \e Bord*) : plateau utilisé pour la recherche des lettres
  */
  void getCrossSetsVertical(const unsigned char & square,
                            char tab_vertical[], bool final,
                            Board* b) const;

  /**
   * @fn void makeMove(const Move & move)
   * @brief Applique un coup sur le plateau
   * @details Met à jour le plateau et les lettres que possèdent le joueur
   * @param[in] move ( \e Move) : coup à jouer
  */
  void makeMove(const Move & move);

  /**
   * @fn void Gen(unsigned char square,int pos, std::string& word,
          char rack[],Node* arc, unsigned char direction,
          Board * b, unsigned short int& score, Move& move,
          unsigned char & j1,
          unsigned char & j2 )
   * @brief fonction récursive de géneration de coups possible
   * @details effectue un appel de fonction avec des paramètres différents selon le contenu de la case courante
   * @param[in] square ( \e unsigned \e char) : case courante
   * @param[in] pos ( \e int) : positionement dans un mot, permet de savoir si on a rencontré le '+'
   * @param[out] word ( \e string) : mot construit pendant la géneration des coups possibles
   * @param[in] rack ( \e char[]) : ensemble de lettres que possède le joueur
   * @param[in] arc ( \e Node*) : positionnement dans le gaddag
   * @param[in] direction ( \e unsigned \e char) : horizontale 'H' ou verticale 'V'
   * @param[in] b ( \e Board*) : plateau du jeu
   * @param[out] score ( \e unsigned \e short \e int) : meilleur score
   * @param[out] move ( \e Move) : meilleur coup
   * @param[out] j1 ( \e unsigned \e char) : indice du premier joker utilisé
   * @param[out] j2 ( \e unsigned \e char) : indice du deuxième joker utilisé
  */
  void Gen(unsigned char square,int pos, std::string& word,
          char rack[],Node* arc, unsigned char direction,
          Board * b, float & score, Move& move,
          unsigned char & j1,
          unsigned char & j2 );

  /**
   * @fn void GoOn(unsigned char square, int pos, char L, std::string & word,
             char rack[],Node * new_arc,Node * old_arc,
             unsigned char direction, Board * b,unsigned short int& score,
             Move& move, unsigned char & j1,
             unsigned char & j2 )
   * @brief fonction récursive de géneration de coups possible
   * @details explore toutes les possibilités pour former un mot, en continuant à avancer dans un sens ou en changeant de direction
   * @param[in] square ( \e unsigned \e char) : case courante
   * @param[in] pos ( \e int) : positionement dans un mot, permet de savoir si on a rencontré le '+'
   * @param[in] L ( \e char) : lettre courante ajoutée au mot formé
   * @param[out] word ( \e string) : mot construit pendant la géneration des coups possibles
   * @param[in] rack ( \e char[]) : ensemble de lettres que possède le joueur
   * @param[in] new_arc ( \e Node*) : positionnement dans le gaddag
   * @param[in] old_arc ( \e Node*) : noeud parent de L dans le gaddag
   * @param[in] direction ( \e unsigned \e char) : horizontale 'H' ou verticale 'V'
   * @param[in] b (\e Board*) : plateau du jeu
   * @param[out] score ( \e unsigned \e short \e int) : meilleur score
   * @param[out] move ( \e Move) : meilleur coup
   * @param[out] j1 ( \e unsigned \e char) : indice du premier joker utilisé
   * @param[out] j2 ( \e unsigned \e char) : indice du deuxième joker utilisé
  */
  void GoOn(unsigned char square, int pos, char L, std::string & word,
            char rack[],Node * new_arc,Node * old_arc,
            unsigned char direction, Board * b, float & score,
            Move& move, unsigned char & j1,
            unsigned char & j2);




  /****************** METHODES PUBLIQUES ******************/


public :

  /**
   * @fn void init()
   * @brief Initialise le jeu
   * @details Initialise le plateau, le sac de lettres, les lettres du joueur ainsi que le plateau
  */
  void init();

  /**
   * @fn void print() const
   * @brief Affiche les paramètres du jeu
   * @details Affiche les lettres que possède le joueur, le plateau et le score
  */
  void print() const;

  /**
   * @fn bool isFinished() const
   * @brief Teste si la partie est terminée
   * @return \e bool : \e true si la partie est terminée, \e false sinon
  */
  bool isFinished() const;

  /**
   * @fn bool emptyBag() const
   * @brief Teste si le sac de lettres est vide
   * @return \e bool : \e true si le sac est vide, \e false sinon
  */
  bool emptyBag() const;

  /**
   * @fn void moveTurn()
   * @brief Fonction qui joue un tour
   * @details Fonction appelée à chaque tour
   * Elle exécute la recherche du meilleur coup, le joue, effectue le tirage des lettres et met à jour le score
  */
  void moveTurn();

  /**
   * @fn void finalPrint() const
   * @brief Affiche les informations en fin de partie
  */
  void finalPrint() const;








  void attribueLettre(const std::string & s, const std::string & s2);

};




/**
 * @fn static std::pair<unsigned char,unsigned char> getIndice(const unsigned char& id)
 * @brief Renvoie un couple de coordonnées à partir d'un indice de case
 * @param[in] id ( \e unsigned \e char) : indice de la case
 * @return \e std::pair<unsigned char, unsigned char> : paire <ligne,colonne>
*/

/**
 * @fn static unsigned short int getIndice(const unsigned char & l,const unsigned char & c)
 * @brief Renvoie un indice de case à partir d'un couple de coordonnées
 * @param[in] l ( \e unsigned \e char) : ligne
 * @param[in] c ( \e unsigned \e char) : colonne
 * @return \e unsigned \e short \e int : indice dans le tableau
*/
