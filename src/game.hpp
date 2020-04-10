/**
 * @file game.hpp
*/


#pragma once


#include <list>
#include <utility>


class Node;
class Board;
class Player;
class Bag;
class Gaddag;
struct Move;



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


public :

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

  /**
   * A FAIRE 
  */ 
  void getCrossSetsHorizontal(const unsigned char & square,
                              char tab_horizontal[], bool final, 
                              Board* b) const;

  /**
   * A FAIRE
  */
  void getCrossSetsVertical(const unsigned char & square,
                            char tab_vertical[], bool final, 
                            Board * b) const;

  /**
   * @fn void makeMove(const Move & move)
   * @brief Applique un coup sur le plateau
   * @details Met à jour le plateau et les lettres que possèdent le joueur
   * @param[in] move ( \e Move) : coup à jouer
  */ 
  void makeMove(const Move & move);

  /**
   * A FAIRE
  */ 
  void Gen(unsigned char square,int pos, std::string& word,
          char rack[],Node* arc, unsigned char direction,
          Board * b, unsigned short int& score, Move& move,
          unsigned char & j1,
          unsigned char & j2 );

  /**
   * A FAIRE
  */ 
  void GoOn(unsigned char square, int pos, char L, std::string & word,
            char rack[],Node * new_arc,Node * old_arc,
            unsigned char direction, Board * b,unsigned short int& score,
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








  void attribueLettre(const std::string & s);


};
