/**
 * @file game.cpp
*/


#include "node.hpp"
#include "gaddag.hpp"
#include "board.hpp"
#include "player.hpp"
#include "bag.hpp"
#include "game.hpp"
#include <stack>
#include <iostream>





/****************** CONSTRUCTEUR / DESTRUCTEUR ******************/



Game::Game(const bool _ia) {
  bag = new Bag();
  player = new Player;
  gad = new Gaddag;
  board = new Board;
  ended = false;
  ia = _ia;
}


Game::~Game() {
  delete board;
  delete player;
  delete bag;
  delete gad;
}




/****************** METHODES PRIVEES ******************/



void Game::printDico() const {
  gad->print();
}


void Game::printHand() const {
  player->printHand();
}


void Game::printBag() const {
  bag->printLetters();
}


void Game::draw(const char & letter) {
  //suppression de la lettre, récupération de l'indice où attribuer la lettre tirée dans le sac
  unsigned short int n = player->removeLetter(letter);
  if (!bag->isEmpty())
    player->setLetter(n,bag->randomDraw());
}


static std::pair<unsigned char,unsigned char> getIndice(const unsigned char& n) {
  unsigned char x = n / 15;
  unsigned char y = n % 15;
  return std::pair<unsigned char,unsigned char>(x,y);
}

static unsigned short int getIndice(const unsigned char & x,
                                    const unsigned char &y) {
  return (x * 15 + y);
}


couple Game::score (const couple & c, const bool & played) const {
  unsigned short int res = bag->getPoints(c.second);
  unsigned short int wf;

  if (played) {   // si la lettre est jouée par le joueur, on compte les facteurs lettre/mot
    res *= static_cast<unsigned short int>(board->getLetterFactor(c.first));
    wf = static_cast<unsigned short int>(board->getWordFactor(c.first));
  }
  else {
    if (board->isJoker(c.first))
      res = 0;
    wf = 1;
  }

  return couple (res,wf);

}


unsigned short int Game::score(const std::list<couple> & l,
                                const std::list<bool> & played) const {
  unsigned short int res = 0;
  unsigned short int wf = 1;
  std::list<couple> l_copy (l);
  std::list<bool> played_copy(played);
  couple temp;

  while(!l_copy.empty()) {
    // calcul des points rapportés par chaque lettre
    temp = score(l_copy.back(),played_copy.back()); //temp.first est le score, temp.second est le word_factor

    res += temp.first;
    if (temp.second > wf)    // on multiplie le score par le meilleur facteur mot possible
      wf = temp.second;
    else if (temp.second == wf)    // 2 facteurs *2 donnent facteur 4 ...
      wf = wf*wf;
    l_copy.pop_back();
    played_copy.pop_back();
  }

  return (wf * res);
}


unsigned short int Game::score(const Board * b,
                              const int & pos,
                              const char & direction) const {

  std::list<couple> l;
  std::list<bool> played;
  couple temp;
  int i = pos;

  if (direction == 'H') {
    while (i >= 0
           && b->getLetter(i) != 0) {
      if (board->isJoker(i))          //la lettre sur le plateau était un joker
        temp = couple(i,'*');
      else
        temp = couple(i,b->getLetter(i));

      l.push_back(temp);
      played.push_back(i == pos);    // i == pos indique si on est sur la case où on joue la lettre
      i -=15 ;
    }
  }

  else if (direction == 'B') {
    while ( i < 225
            && b->getLetter(i) != 0) {
      if (board->isJoker(i))
        temp = couple(i,'*');      //la lettre sur le plateau était un joker
      else
        temp = couple(i,b->getLetter(i));

      l.push_back(temp);
      played.push_back(i == pos);
      i +=15 ;
    }
  }

  else if (direction == 'G') {

    while ( getIndice(pos).first == getIndice(i).first
            && b->getLetter(i) != 0) {

      if (board->isJoker(i))
        temp = couple(i,'*');     //la lettre sur le plateau était un joker
      else
        temp = couple(i,b->getLetter(i));

      l.push_back(temp);
      played.push_back(i == pos);
      i -= 1 ;
    }
  }

  else { //direction == 'D'

    while ( getIndice(pos).first == getIndice(i).first
            && b->getLetter(i) != 0) {
      if (board->isJoker(i))
        temp = couple(i,'*');     //la lettre sur le plateau était un joker
      else
        temp = couple(i,b->getLetter(i));

      l.push_back(temp);
      played.push_back(i == pos);
      i += 1;
    }
  }
  return score(l,played);
}



unsigned short int Game::bonusScore(const unsigned char & board_pos,
                                    const char & temp_word,
                                    const char & direction,
                                    const int fq) const {
  unsigned short int pts = 0;
  int i = fq;
  if (i > 224)
    i = static_cast<int>(board_pos);

  //copie du plateau, insertion de la lettre et calcul du score bonus
  Board * b_copy = new Board(*this->board);
  b_copy->setLetter(board_pos,temp_word);

  pts =  score(b_copy,i,direction);
  delete b_copy;
  return pts;
}


unsigned short int Game::score (const Move & m) const {

  unsigned int pos = static_cast<unsigned int> (m.first_square); //position initiale
  unsigned short int points = 0;
  unsigned short int nb_letters_used = 0; //compteur lettres utiliséés pour le bonus de 50pts
  unsigned int board_pos = pos; //positionnement en fonction du mouvement à effectuer
  couple temp_couple;
  char temp_word; //lettre à jouer sur la case
  unsigned int temp_pos = 0;
  std::list<couple> move; //liste de couple (association <case,lettre>)
  std::list<bool> played; //liste de booléens qui indique si la lettre est posée par je joueur ou déjà sur le plateau

  if (m.direction == 'H') {               //On joue vers le HAUT

    int word_pos = static_cast<int>(m.word.size() - 1);

    while ( word_pos >= 0
            && board_pos < 225) {

      if (board->getLetter(board_pos) == 0) {
        played.push_back(true);
        nb_letters_used++;

        if (board_pos == m.j1 || board_pos == m.j2) {  //cas d'utilisation d'un joker
          temp_word = '*';
        }
        else {
          temp_word = m.word[word_pos];
        }

        if ( getIndice(board_pos).first == getIndice(board_pos - 1).first
              && board->getLetter(board_pos - 1) != 0) { //lettre à gauche
          temp_pos = board_pos;
          while ( getIndice(board_pos).first == getIndice(temp_pos + 1).first
                  && board->getLetter(temp_pos + 1) != 0 ) { //tant que lettre à droite
            temp_pos++;
          }
          points += bonusScore(board_pos,temp_word,'G',temp_pos);
        }
        else if ( getIndice(board_pos).first == getIndice(board_pos + 1).first
                  && board->getLetter(board_pos + 1) != 0) {   //lettre à droite uniquement
          points += bonusScore(board_pos,temp_word,'D');

        }

      }
      else {
        played.push_back(false);
        temp_word = m.word[word_pos];
      }
      temp_couple = couple (board_pos,temp_word);
      move.push_back(temp_couple);
      board_pos -= 15;
      word_pos--;

    }

  }

  else if (m.direction == 'B')  {        //On joue vers le BAS

    unsigned int word_pos = 0;

    while ( word_pos < m.word.size()
            && board_pos < 225) {

      if (board->getLetter(board_pos) == 0) {
        played.push_back(true);
        nb_letters_used++;

        if (board_pos == m.j1 || board_pos == m.j2) {  //cas d'utilisation d'un joker
          temp_word = '*';
        }
        else {
          temp_word = m.word[word_pos];
        }
        if ( getIndice(board_pos).first == getIndice(board_pos - 1).first
            &&  board->getLetter(board_pos - 1) != 0) { //lettre à gauche
          temp_pos = board_pos;
          while ( getIndice(board_pos).first == getIndice(temp_pos + 1).first
                  && board->getLetter(temp_pos + 1) != 0 ) { //tant que lettre à droite
            temp_pos++;
          }
          points += bonusScore(board_pos,temp_word,'G', temp_pos);
        }

        else if ( getIndice(board_pos).first == getIndice(board_pos + 1).first
                  && board->getLetter(board_pos + 1) != 0) {   //lettre à droite uniquement
          points += bonusScore(board_pos,temp_word,'D');
        }

      }
      else {
        played.push_back(false);
        temp_word = m.word[word_pos];
      }
      temp_couple = couple (board_pos,temp_word);
      move.push_back(temp_couple);
      board_pos += 15;
      word_pos++;
    }
  }

  else if (m.direction =='G') {          //On joue vers la GAUCHE

    int word_pos = static_cast<int>(m.word.size() - 1);

    while ( word_pos >= 0
            && getIndice(board_pos).first == getIndice(pos).first ) {

      if (board->getLetter(board_pos) == 0) {
        played.push_back(true);
        nb_letters_used++;

        if (board_pos == m.j1 || board_pos == m.j2) {  //cas d'utilisation d'un joker
          temp_word = '*';
        }
        else {
          temp_word = m.word[word_pos];
        }

          if ( board_pos > 14 && board_pos < 225
              &&  board->getLetter(board_pos - 15) != 0) {   //lettre en haut

            temp_pos = board_pos;
            while ( temp_pos < 210
                    && board->getLetter(temp_pos + 15) != 0 ) {   //tant que lettre en bas
              temp_pos += 15;
            }
          points += bonusScore(board_pos,temp_word,'H',temp_pos);
        }

        else if ( board_pos < 210
                && board->getLetter(board_pos + 15) != 0) {   //lettre  en bas uniquement
          points += bonusScore(board_pos,temp_word,'B');
        }

      }
      else {
        played.push_back(false);
        temp_word = m.word[word_pos];
      }
      temp_couple = couple (board_pos,temp_word);
      move.push_back(temp_couple);
      board_pos--;
      word_pos--;
    }

  }

  else {        //On joue vers la DROITE

    unsigned int word_pos = 0;

    while ( word_pos < m.word.size()
            && getIndice(pos).first == getIndice(board_pos).first) {

      if (board->getLetter(board_pos) == 0) {
        played.push_back(true);
        nb_letters_used++;

        if (board_pos == m.j1 || board_pos == m.j2) {  //cas d'utilisation d'un joker
          temp_word = '*';
        }
        else {
          temp_word = m.word[word_pos];
        }

        if ( board_pos > 14 && board_pos < 225
            &&  board->getLetter(board_pos - 15) != 0) {   //lettre en haut

          temp_pos = board_pos;

          while ( temp_pos < 210
                  && board->getLetter(temp_pos + 15) != 0 ) {   //tant que lettre en bas
            temp_pos += 15;
          }
          points += bonusScore(board_pos,temp_word,'H',temp_pos);
        }
        else if ( board_pos < 210
                  && board->getLetter(board_pos + 15) != 0) { //lettre  en bas uniquement
          points += bonusScore(board_pos,temp_word,'B');
        }
      }
      else {
        played.push_back(false);
        temp_word = m.word[word_pos];
        if (board->isJoker(board_pos))
          temp_word = '*';
      }
      temp_couple = couple (board_pos,temp_word);
      move.push_back(temp_couple);
      board_pos++;
      word_pos++;
    }
  }

  points += score(move,played);
  if (nb_letters_used == 7)
    points += 50;
  return points;

}

//calcul de la valeur du rack, méthode de Gordon

float Game::grade(const char rack[]) const {

  float grade = 0;
  int letters_used[27] = {0};
  int nb_vowels = 0;
  int nb_letters_used = 0;

  for (unsigned int i = 0; i < 7 ; i++) {

    if (rack[i] == '/')
      continue;

    else if (rack[i] == '*') {
      grade += bag->getWeight1('*');
      grade += letters_used[26] * bag->getWeight2('*');
      letters_used[26]++;
    }

    else {
      grade += bag->getWeight1(rack[i]);
      grade += letters_used[rack[i] - 'A'] * bag->getWeight2(rack[i]);
      nb_letters_used++;
      letters_used[rack[i] - 'A']++;
    }

  }

  nb_vowels += letters_used['A' - 'A'];
  nb_vowels += letters_used['E' - 'A'];
  nb_vowels += letters_used['I' - 'A'];
  nb_vowels += letters_used['O' - 'A'];
  nb_vowels += letters_used['U' - 'A'];
  nb_vowels += letters_used['Y' - 'A'];

  grade += bag->getRatio(nb_vowels,(nb_letters_used - nb_vowels));

  return grade;

}


void Game::makeMove(const Move & m) {

  unsigned short int board_pos = static_cast<unsigned short int>(m.first_square);
  bool joker;

  if (m.direction == 'H') {  // On joue vers le HAUT
    int word_pos = static_cast<int>(m.word.size() - 1);
    while (word_pos >= 0) {
      if (board->getLetter(board_pos) == 0) {
        joker = (board_pos != m.j1 && board_pos != m.j2);  // teste si un joker est utilisé pour formé le mot
        board->setLetter(board_pos,m.word[word_pos],joker); 
        if (joker) {          
          draw(m.word[word_pos]);   //on tire une lettre pour remplacer celle jouée
        }
        else {
          draw('*');   //on tire une lettre pour remplacer le joker
        }
      }
      word_pos--;
      board_pos -= 15;
    }
  }

    else if (m.direction == 'B') {  // On joue vers le BAS
      unsigned short int word_pos = 0;
      while (word_pos < m.word.size()) {
        if (board->getLetter(board_pos) == 0) {
          joker = (board_pos != m.j1 && board_pos != m.j2);
          board->setLetter(board_pos,m.word[word_pos],joker);
          if (joker) {
            draw(m.word[word_pos]);
          }
          else {
            draw('*');
          }
        }
        word_pos++;
        board_pos += 15;
      }
    }

      else if (m.direction == 'D') {   // On joue vers la DROITE
        unsigned short int word_pos = 0;
        while (word_pos < m.word.size()) {
          if (board->getLetter(board_pos) == 0) {
            joker = (board_pos != m.j1 && board_pos != m.j2);
            board->setLetter(board_pos,m.word[word_pos],joker);
            if (joker) {
              draw(m.word[word_pos]);
            }
            else {
              draw('*');
            }
          }
          word_pos++;
          board_pos++;
        }
      }

        else {    // On joue vers la GAUCHE
          int word_pos = static_cast<int>(m.word.size() - 1);
          while (word_pos >= 0) {
            if (board->getLetter(board_pos) == 0) {
              joker = (board_pos != m.j1 && board_pos != m.j2);
              board->setLetter(board_pos,m.word[word_pos],joker);
              if (joker) {
                draw(m.word[word_pos]);
              }
              else {
                draw('*');
              }
            }
            word_pos--;
            board_pos--;
          }
        }

}


void Game::getCrossSetsHorizontal(const unsigned char & square,
                                  char tab_horizontal[], bool final, Board * b) const {
  unsigned char x = (getIndice(square)).first;
  unsigned char y = (getIndice(square)).second;
  char l;

  // dans le cas ou la case est vide
  if(b->getLetter(x,y) == 0) {
    // dans le cas où la case est adjacente à une case vide
    // directement à droite (case non vide à gauche)
    if( (((y < 14) && (b->getLetter(x, y+1) == 0))
        || (y >= 14))
        && (y > 0)
        && (b->getLetter(x, y-1) != 0)) {

          l = b->getLetter(x, y-1);
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupère les lettres présentes sur le plateau
          // en avançant simultanément sur le gaddag
          while((l != 0)
                && (y - i >= 0) ) {
            gad_parcours = gad_parcours->getNode(l);

            if (y-1-i >= 0)
              l = b->getLetter(x, y-1-i);
            else
              l = 0;

            i++;
          }
          // je change de direction
          if(gad_parcours != nullptr)
            gad_parcours = gad_parcours->getNode('+');

          for(int i = 0; i < 26; i++) {
            // je récupère les noeuds fils du '+'
            if(gad_parcours != nullptr && gad_parcours->getNode(i) != nullptr){
              if(final){ // dans le cas où je cherche des lettres finales
                if((gad_parcours->getNode(i))->isFinal())
                  tab_horizontal[i] = gad->getLetter(i);
                else
                  tab_horizontal[i] = '/';
              }
              else tab_horizontal[i] = gad->getLetter(i);
            }
            else
            {
              tab_horizontal[i] = '/';
            }
          }
    }
    // dans le cas où la case est adjacente à une case vide
    // directement à gauche (case non vide à droite)
    else if( (y < 14)
          && (b->getLetter(x,y+1) != 0)
          && (((y > 0)
          && (b->getLetter(x,y-1) == 0))
          || (y <= 0))) {

          std::stack<char> pile;
          l = b->getLetter(x, y+1);
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupère les lettres présentes sur le plateau dans une pile
          while((l != 0)
                && (y + i <= 14) ) {
            pile.push(l);

            if (y+1+i <= 14)
              l = b->getLetter(x, y+1+i);
            else
              l = 0;

            i++;
          }
          // J'avance dans le gaddag en dépilant
          while (!pile.empty()) {
            gad_parcours = gad_parcours->getNode(pile.top());
            pile.pop();
          }
          // je récupère les noeuds fils accesible depuis le noeud courant
          for(int i = 0; i < 26; i++) {

            if(gad_parcours != nullptr && gad_parcours->getNode(i) != nullptr){
              if(final){ //dans le cas où je cherche des lettres finales
                if(gad_parcours->getNode(i)->getNode('+') != nullptr &&
                  (gad_parcours->getNode(i)->getNode('+'))->isFinal())
                  tab_horizontal[i] = gad->getLetter(i);
                else
                  tab_horizontal[i] = '/';
              }
              else tab_horizontal[i] = gad->getLetter(i);
            }
            else
            {
              tab_horizontal[i] = '/';
            }
          }
    }
    // dans le cas où la case se trouve entre deux cases non vides
    else if ((y < 14)
            && (b->getLetter(x,y+1) != 0)
            && (y > 0)
            && (b->getLetter(x,y-1) != 0)){

          l = b->getLetter(x, y-1);
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupére la premier mot sur le plateau à l'envers
          // en avançant simultanément sur le gaddag
          while((y - i >= 0)
                && (l != 0)){
            gad_parcours = gad_parcours->getNode(l);

            if (y-1-i >= 0)
              l = b->getLetter(x, y-1-i);
            else
              l = 0;

            i++;
          }
          // je change de direction
          gad_parcours = gad_parcours->getNode('+');
          Node * copy = gad_parcours;

          for (int i = 0; i < 26; i++) {

            copy = gad_parcours;

            if (copy != nullptr && copy->getNode(i) != nullptr) {
              // j'avance sur le gaddag avec la lettre 'A' + i
              copy = copy->getNode(i);
              Node* gad_coup_possible = copy;
              l = b->getLetter(x, y+1);
              int j = 1;
              // j'avance sur le gaddag avec le deuxième mot présent sur le plateau
              while( gad_coup_possible != nullptr
                    && l != 0 ) {
                gad_coup_possible = gad_coup_possible->getNode(l);

                if (y+1+j <= 14)
                  l = b->getLetter(x, y+1+j);
                else
                  l = 0;

                j++;
              }
              // je teste si je forme un mot existant dans le dictionnaire
              if (gad_coup_possible != nullptr
                  && l == 0
                  && gad_coup_possible->isFinal() ) {
                tab_horizontal[i] = gad->getLetter(i);
              }
              else
              {
                tab_horizontal[i] = '/';
              }
            }
            else
            {
                tab_horizontal[i] = '/';
            }
          }
    }
    else
    { // dans le cas où la case est vide, avec des cases vides autour
      for(int i = 0; i < 26; i++){
        // toutes les lettres sont jouables
        tab_horizontal[i] = gad->getLetter(i);
      }
    }

  }
  else
  { // dans le cas où la case est non vide
    for(int i = 0; i < 26; i++){
      // aucune lettre n'est jouable sur cette case
      tab_horizontal[i] = '/';
    }
  }

}

void Game::getCrossSetsVertical(const unsigned char & square,
                                  char tab_vertical[], bool final, Board * b) const {

  unsigned char x = (getIndice(square)).first;
  unsigned char y = (getIndice(square)).second;
  char l;

  // dans le cas ou la case est vide
  if (b->getLetter(x, y) == 0){
    // dans le cas où la case est adjacente à une case vide
    // directement à droite (case non vide à gauche)
    if( (((x < 14) && (b->getLetter(x+1, y) == 0))
        || (x >= 14))
        && (x > 0)
        && (b->getLetter(x-1, y) != 0)) {

          l = b->getLetter(x-1, y);

          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupère les lettres présentes sur le plateau
          // en avançant simultanément sur le gaddag
          while((l != 0)
                && (x - i >= 0) ) {
            gad_parcours = gad_parcours->getNode(l);


            if (x-1-i >= 0)
              l = b->getLetter(x-1-i, y);
            else
              l = 0;

            i++;
          }
          // je change de direction
          if(gad_parcours != nullptr)
            gad_parcours = gad_parcours->getNode('+');

          for(int i = 0; i < 26; i++) {
            // je récupère les noeuds fils du '+'
            if(gad_parcours != nullptr && gad_parcours->getNode(i) != nullptr){
              if(final){// dans le cas où je cherche des lettres finales
                if((gad_parcours->getNode(i))->isFinal())
                  tab_vertical[i] = gad->getLetter(i);
                else
                  tab_vertical[i] = '/';
              }
              else tab_vertical[i] = gad->getLetter(i);

            }
            else
            {
              tab_vertical[i] = '/';
            }
          }
    }
    // dans le cas où la case est adjacente à une case vide
    // directement à gauche (case non vide à droite)
    else if( (x < 14)
          && (b->getLetter(x+1, y) != 0)
          && (((x > 0)
          && (b->getLetter(x-1, y) == 0))
          || (x <= 0))) {

          std::stack<char> pile;
          l = b->getLetter(x+1, y);
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupère les lettres présentes sur le plateau dans une pile
          while((l != 0)
                && (x + i <= 14) ) {
            pile.push(l);

            if (x+1+i <= 14)
              l = b->getLetter(x+1+i, y);
            else
              l = 0;

            i++;
          }
          // J'avance dans le gaddag en dépilant
          while (!pile.empty()) {
            gad_parcours = gad_parcours->getNode(pile.top());
            pile.pop();
          }
          // je récupère les noeuds fils accesible depuis le noeud courant
          for(int i = 0; i < 26; i++) {

            if(gad_parcours != nullptr && gad_parcours->getNode(i) != nullptr){
              if(final){// dans le cas où je cherche des lettres finales
                if(gad_parcours->getNode(i)->getNode('+') != nullptr &&
                  (gad_parcours->getNode(i)->getNode('+'))->isFinal())
                  tab_vertical[i] = gad->getLetter(i);
                else
                  tab_vertical[i] = '/';
              }
              else tab_vertical[i] = gad->getLetter(i);

            }
            else
            {
              tab_vertical[i] = '/';
            }
          }
    }
    // dans le cas où la case se trouve entre deux cases non vides
    else if ((x < 14)
            && (b->getLetter(x+1, y) != 0)
            && (x > 0)
            && (b->getLetter(x-1, y) != 0)){

          l = b->getLetter(x-1, y);
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupére la premier mot sur le plateau à l'envers
          // en avançant simultanément sur le gaddag
          while((x - i >= 0)
                && (l != 0)){
            gad_parcours = gad_parcours->getNode(l);

            if (x-1-i >= 0)
              l = b->getLetter(x-1-i, y);
            else
              l = 0;

            i++;
          }
          // je chande de direction
          gad_parcours = gad_parcours->getNode('+');
          Node * copy = gad_parcours;

          for (int i = 0; i < 26; i++) {

            copy = gad_parcours;

            if (copy != nullptr && copy->getNode(i) != nullptr) {
              // j'avance sur le gaddag avec la lettre 'A' + i
              copy = copy->getNode(i);
              Node* gad_coup_possible = copy;
              l = b->getLetter(x+1, y);
              int j = 1;
              // j'avance sur le gaddag avec le deuxième mot présent sur le plateau
              while( gad_coup_possible != nullptr
                    && l != 0 ) {
                gad_coup_possible = gad_coup_possible->getNode(l);

                if (x+1+j <= 14)
                  l = b->getLetter(x+1+j, y);
                else
                  l = 0;

                j++;
              }
              // je teste si je forme un mot existant dans le dictionnaire
              if (gad_coup_possible != nullptr
                  && l == 0
                  && gad_coup_possible->isFinal() ) {

                tab_vertical[i] = gad->getLetter(i);
              }
              else
              {
                tab_vertical[i] = '/';
              }

            }
            else
            {
                tab_vertical[i] = '/';
            }
          }
    }
    else { // dans le cas où la case est vide, avec des cases vides autour
      for(int i = 0; i < 26; i++) {
        // toutes les lettres sont jouables
        tab_vertical[i] = gad->getLetter(i);
      }
    }

  }
  else { // dans le cas où la case est non vide
    for(int i = 0; i < 26; i++) {
      // aucune lettre n'est jouable sur cette case
      tab_vertical[i] = '/';
    }
  }
}


void Game::Gen(unsigned char square, int pos, std::string& word,
         char rack[], Node* arc, unsigned char direction,
         Board* b, float & points, Move& move,
         unsigned char & j1,
         unsigned char & j2){

  unsigned char x = (getIndice(square)).first;
  unsigned char y = (getIndice(square)).second;
  char letter = b->getLetter(square);

  if(letter != 0) {
    Node* next_arc = arc->getNode(letter);
    GoOn(square, pos,letter, word, rack, next_arc, arc, direction, b, points, move, j1, j2);
  }
  else
  {
    char tab_horizontal[26];
    char tab_vertical[26];

    if(direction == 'H'){
      getCrossSetsHorizontal(square,tab_horizontal, false, b);
      getCrossSetsVertical(square,tab_vertical, true, b);
    }
    // sinon je me déplace verticalement et donc les cross sets horizontales
    // doivent être des lettres finales
    else
    {
      getCrossSetsHorizontal(square,tab_horizontal, true, b);
      getCrossSetsVertical(square,tab_vertical, false, b);
    }

    // Je copie mes paramètres de fonctions afin de ne pas les perdre dans les
    // appels récursifs
    unsigned char square_copy = square;
    int pos_copy = pos;
    std::string word_copy = word;
    Board b_copy(*b);
    Node* arc_copy = arc;
    char rack_copy[7];
    unsigned short int points_copy = points;
    unsigned char j1_copy = j1;
    unsigned char j2_copy = j2;
    char temp;
    unsigned short int i,j,k;

    for (i = 0; i < 7; i++){
      rack_copy[i] = rack[i];
    }


    for (i = 0; i < 7; i++) {

      // Je remets les paramètres à leur état initial avant chaque itération
      square = square_copy;
      pos = pos_copy;
      word = word_copy;
      *b = b_copy;
      arc = arc_copy;
      j1 = j1_copy;
      j2 = j2_copy;

      for (j = 0; j < 7; j++) {
        rack[j] = rack_copy[j];
      }

      // Dans le cas où le rack contient un joker
      if(rack[i] == '*'){

        if(j1 != 255 || j2 != 255){
          if(b->getLetter(j1) == 0){
            j1 = j2;
            j2 = 255;
          }
          if(b->getLetter(j2) == 0){
            j2 = 255;
          }
        }

        if (j1 != 255) // Si j1 == 255, cela veut dire qu'on a utilisé aucun joker
          j2 = square; // Je sauvegarde la position du joker
        else
          j1 = square;

        // Je copie la position des jokers pour ne pas la perdre dans les appels
        unsigned char j1_copy2 = j1;
        unsigned char j2_copy2 = j2;


        for(j = 0; j < 26; j++){
          // Je remets les paramètres à leur état initial avant chaque itération
          if(tab_horizontal[j] != '/' && tab_vertical[j] != '/'){
            square = square_copy;
            pos = pos_copy;
            word = word_copy;
            *b = b_copy;
            arc = arc_copy;
            j1 = j1_copy2;
            j2 = j2_copy2;

            for (k = 0; k < 7; k++) {
              rack[k] = rack_copy[k];
            }

            rack[i] = '/'; // Je supprime le joker dans le rack
            Node* next_arc = arc->getNode(j); // J'avance dans le gaddag avec la lettre qu'il représente
            b->setLetter(square,'A' + j); // Je place la lettre sur le plateau
            GoOn(square, pos,'A' + j, word, rack, next_arc, arc, direction, b, points,move, j1, j2);
          }
        }
      }
      // Pour chaque lettre que possède le joueur, jouable sur cette case
      // je génère des coups possibles
      else if((rack[i] != '/')
              && (tab_horizontal[rack[i] - 'A'] != '/')
              && (tab_vertical[rack[i] - 'A'] != '/')){
          temp = rack[i]; // Je copie la lettre que je joue avant la supprimer
          rack[i] = '/'; // Je supprime la lettre du rack
          Node* next_arc = arc->getNode(temp - 'A'); // J'avance sur le gaddag
          b->setLetter(square,temp); // Je place la lettre sur le plateau
          GoOn(square, pos, temp, word, rack, next_arc, arc, direction, b, points,move, j1, j2);
        }
    }

  }
}


void Game::GoOn(unsigned char  square, int pos, char L,std:: string& word,
          char rack[],Node* new_arc,
          Node* old_arc,unsigned char direction,
          Board* b, float & points, Move& move,
          unsigned char & j1,
          unsigned char & j2) {

  unsigned char x = (getIndice(square)).first;
  unsigned char y = (getIndice(square)).second;

  if(pos <= 0 ){ // se déplacer à gauche

      // Je concatène la lettre jouée à gauche du mot
      word = L + word;

      if(new_arc != nullptr){
        //j'avance dans le gaddag et le plateau simultanément
        if(direction == 'H'){
          if(y-1 >= 0){
            // je continue à gauche
            unsigned int suivant = getIndice(x,y-1);
            Gen(suivant, pos-1, word, rack, new_arc, direction, b, points, move, j1, j2);
          }

           // Je change de direction
          new_arc = new_arc->getNode('+');

          // Si la nouvelle branche du gaddag n'est pas vide et la case directement
          // à gauche est vide
          if ((new_arc != nullptr)
              && (((y-1>= 0)
              && (b->getLetter(x,y-1) == 0))
              || (y-1 < 0))){

                // Si la branche est finale, et qu'il n'y a pas de case non vide
                // à droite j'enregistre un coup possible
                if((new_arc->isFinal())
                  && ((y-pos+1 >14) || ((y-pos+1 <=14)
                  && (b->getLetter(x,y-pos+1) == 0)))){

                    Move new_move (word,getIndice(x, y),'D', j1, j2);

                    // Appel de la fonction qui calcule le score
                    float new_points;
                    if (ia)
                      new_points =  grade(rack) + 2*score(new_move); // = l'appel récursif
                    else
                      new_points = score(new_move);

                    // Si le score calculé est meilleur, on garde le dernier coup
                    if (new_points > points){
                      move = new_move;
                      points = new_points;
                    }
                  }
                // Sinon je continue toujours à droite
                if(y-pos+1 <= 14){
                  unsigned int suivant = getIndice(x,y-pos+1);
                  Gen(suivant, 1, word, rack, new_arc, direction, b, points, move, j1, j2);
                }

              }

        } // dans le cas ou direction == V , je joue verticalement avec le même raisonnement
        else{
          unsigned char j1_copy = j1;
          unsigned char j2_copy = j2;

          if(x-1 >= 0){
            unsigned int suivant = getIndice(x-1,y);
            Gen(suivant, pos-1, word, rack, new_arc, direction, b, points, move, j1, j2);
          }
          j1 = j1_copy;
          j2 = j2_copy;
          new_arc = new_arc->getNode('+');

          if ((new_arc != nullptr)
              && (((x-1 >= 0)
              && (b->getLetter(x-1,y) == 0))
              || (x-1 < 0))){

                if((new_arc->isFinal())
                  && ((x-pos+1 >14) || ((x-pos+1 <=14)
                  && (b->getLetter(x-pos+1,y) == 0)))){

                    Move new_move(word,getIndice(x, y),'B', j1, j2);
                    float new_points;
                    if (ia)
                      new_points =  grade(rack) + 2*score(new_move); // = l'appel récursif
                    else
                      new_points = score(new_move);
                    if (new_points > points){
                      move = new_move;
                      points = new_points;
                    }
                  }

                if(x-pos+1 <= 14){
                  unsigned int suivant = getIndice(x-pos+1,y);
                  Gen(suivant, 1, word, rack, new_arc, direction, b, points, move, j1, j2);
                }
              }
        }
      }
  }
  else if (pos > 0){ // Se déplacer à droite

    // Je concatène la lettre jouée à gauche du mot
    word = word + L;

    if((new_arc != nullptr) && (new_arc->isFinal())){

      // Si la branche est finale , et qu'il n'y a pas de case non vide
      // directement à droite, j'enregistre un coup possible
      if(direction == 'H'){ // Horizontalement

        if (((y + 1 <= 14)
            && (b->getLetter(x,y+1) == 0))
            ||(y + 1 > 14)){

              Move new_move (word,square,'G', j1, j2);

              // Appel de la fonction qui calcule le score
              float new_points;
              if (ia)
                new_points =  grade(rack) + 2*score(new_move);
              else
                new_points = score(new_move);

              // Si le score calculé est meilleur, on garde le dernier coup
              if (new_points > points){
                move = new_move;
                points = new_points;
              }
        }
      }
      else { // verticalement
        if (((x + 1 <= 14)
            && (b->getLetter(x+1,y) == 0))
            ||(x + 1 > 14)){

              Move new_move = Move (word,getIndice(x, y),'H', j1, j2);

              // Appel de la fonction qui calcule le score
              float new_points;
              if (ia)
                new_points =  grade(rack) + 2*score(new_move);
              else
                new_points = score(new_move);

              // Si le score calculé est meilleur, on garde le dernier coup
              if (new_points > points){
                move = new_move;
                points = new_points;
              }
        }
      }
    }
    // Sinon je continue d'avancer à droite
    if(new_arc != nullptr){
      if(direction == 'H'){
        if(y+1 <= 14){
          unsigned int suivant = getIndice(x,y+1);
          Gen(suivant, pos+1, word, rack, new_arc, direction, b, points, move, j1, j2);
        }

      }
      else{
        if(x+1 <= 14){
          unsigned int suivant = getIndice(x+1,y);
          Gen(suivant, pos+1, word, rack, new_arc, direction, b, points, move, j1, j2 );
        }
      }
    }
  }
}




/****************** METHODES PUBLIQUES ******************/



void Game::init() {
  unsigned int i = 0;
  while (i < 7) {
    player->setLetter(i,bag->randomDraw());
    i++;
  }
  gad->addDictionnary();
}


void Game::print() const {
  std:: cout << std::endl << "Rack : " << std::flush;
  player->printHand();
  std::cout << std::endl << *board << std::endl;
  std::cout << "Score : " << player->getPoints() << std::endl
            << std::endl << std::endl;

}


bool Game::isFinished() const {
  return  (ended);
}


bool Game::emptyBag() const {
  return (bag->isEmpty());
}


void Game::moveTurn() {

  std::string word;
  char table[7];

  // J'initialise le rack avec les lettres du joueur
  for (unsigned short int i = 0; i < 7; i++) {
    table[i] = player->getLetter(i);
  }

  Node * parcours = gad->getFirst();
  Board b(*(board)); // Je travaille sur une copie du plateau
  float s = -10000.0;
  Move m;
  unsigned char j1 = 255, j2 = 255;

  // Je récupère les cases à partir desquelles je peux générer des coups possibles
  std::list<unsigned char> anchor_squares = board->getAnchorSquares();

  // Si le plateau est vide (au début de la partie), je génère le meilleur coup
  // en partant du milieu

  if (anchor_squares.empty()){
    Gen(112,0,word,table,parcours,'H',&b,s,m, j1, j2);
  }

  while(!anchor_squares.empty()){

    // Avant chaque itération je remets les paramètres à leur état initial
    word = "";
    for (unsigned short int i = 0; i < 7; i++) {
      table[i] = player->getLetter(i);
    }
    b = *board;
    j1 = 255;
    j2 = 255;
    // La géneration des mots horizontaux
    Gen(anchor_squares.back(),0,word,table,parcours,'H',&b,s,m,j1,j2);

    // Avant l'appel à Gen pour la génération des mots verticaux
    // je remets les paramètres à leur état initial
    word = "";
    for (unsigned short int i = 0; i < 7; i++) {
      table[i] = player->getLetter(i);
    }
    b = *board;
    j1 = 255;
    j2 = 255;

    Gen(anchor_squares.back(),0,word,table,parcours,'V',&b,s,m,j1,j2);

    anchor_squares.pop_back();
  }

  // Si le meilleur coup rapporte un score de -10000 , cela veut dire que la partie est terminée
  if(s == -10000){
    ended = true;
  }
  else {
    s = score(m);

    std::cout << "Le coup joué est " << m.word
              << " à partir de " << static_cast<int>(m.first_square)
              <<" vers "<< m.direction << " et il rapporte " << s
              <<" points" << std::endl;

    player->addPoints(s); // Ajouter les points rapportées par le coup au score
    makeMove(m); // Jouer le mot sur le plateau
  }

}


void Game::finalPrint() const {
  if (ended && bag->isEmpty()) {
    std::cout << "Le joueur ne peut plus jouer et le sac est vide."
              << std::endl;
  }
  else {
    std::cout << "Le joueur est bloqué !"
              << std::endl << std::endl 
              << "Lettres restantes" << std::endl;
    printBag();
    std::cout << std::endl;
  }
  std::cout << "Partie terminée..." << std::endl
            << "Le joueur termine avec un score de "
            << player->getPoints() << std::endl;
}







void Game::attribueLettre(const std::string s, const std::string s2) {
  unsigned int i = 0;
  unsigned int size = s.size();

  for (i = 0; i < s2.size(); i++) {
    bag->removeLetter(s2[i]);
  }

  for (i = 0; i < size; i++) {
    player->setLetter(i,s[i]);
    bag->removeLetter(s[i]);
  }

  while (i < 7) {
    player->removeLetterIndice(i);
    i++;
  }


  for (unsigned int i = 0; i < 225; i++) {
    if (board->getLetter(i) != 0)
      bag->removeLetter(board->getLetter(i));
  }

}
