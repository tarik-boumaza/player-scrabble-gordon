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



static void printList(const std::list<couple> & l) {
  std::list<couple> copy(l);
  std::cout << std::endl <<  "print list couple" << std::endl;
  while(!copy.empty()) {
    std::cout << copy.back().first << " ; " << copy.back().second << std::endl;
    copy.pop_back();
  }
  std::cout << std::endl;
}


static void printList(const std::list<bool> & l) {
  std::list<bool> copy(l);
  std::cout << std::endl <<  "print list bool" << std::endl;
  while(!copy.empty()) {
    std::cout << copy.back() << std::endl;
    copy.pop_back();
  }
  std::cout << std::endl;
}





/****************** CONSTRUCTEUR / DESTRUCTEUR ******************/



Game::Game() {
  bag = new Bag("./data/letters.txt","./data/points.txt");
  player = new Player;
  gad = new Gaddag;
  board = new Board;
  ended = false;
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
    //std::cout << "Lettre " << static_cast<char>((l_copy.back().second))
    //                        << " : + " << static_cast<int>(temp.first)
    //                        << " pts" << std::endl;

    res += temp.first;
    if (temp.second > wf)    // on multiplie le score par le meilleur facteur mot possible
      wf = temp.second;
    l_copy.pop_back();
    played_copy.pop_back();
  }

  return (wf * res);
}


unsigned short int Game::score(const Board * b, const int & pos,
                                const char & direction) const {

  int i = pos;
  std::list<couple> l;
  std::list<bool> played;
  couple temp;

  temp = couple(i,b->getLetter(i));
  l.push_back(temp);
  played.push_back(true);

  if (direction == 'H') {
    i -= 15;
    while (i >= 0
           && b->getLetter(i) != 0) {
      if (board->isJoker(i))
        temp = couple(i,'*');
      else
        temp = couple(i,b->getLetter(i));
      l.push_back(temp);
      played.push_back(false);
      i -=15 ;
    }
  }

  else if (direction == 'B') {
    i += 15;
    while ( i < 225
            && b->getLetter(i) != 0) {
      if (board->isJoker(i))
        temp = couple(i,'*');
      else
        temp = couple(i,b->getLetter(i));
      l.push_back(temp);
      played.push_back(false);
      i +=15 ;
    }
  }

  else if (direction == 'G') {
    i -= 1;
    while ( getIndice(pos).first == getIndice(i).first
            && b->getLetter(i) != 0) {
      if (board->isJoker(i))
        temp = couple(i,'*');
      else
        temp = couple(i,b->getLetter(i));

      l.push_back(temp);
      played.push_back(false);
      i -= 1 ;
    }
  }

  else { //direction == 'D'
    i += 1;
    while ( getIndice(pos).first == getIndice(i).first
            && b->getLetter(i) != 0) {
      if (board->isJoker(i))
        temp = couple(i,'*');
      else
        temp = couple(i,b->getLetter(i));
      l.push_back(temp);
      played.push_back(false);
      i += 1;
    }
  }
  return score(l,played);
}



unsigned short int Game::bonusScore(const unsigned char & board_pos,
                                    const char & temp_word,
                                    const char & direction) const {
  unsigned short int pts = 0;

  Board * b_copy = new Board(*this->board);
  b_copy->setLetter(board_pos,temp_word);
  pts =  score(b_copy, board_pos, direction);
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
          while ( getIndice(pos).first == getIndice(temp_pos + 1).first
                  && board->getLetter(temp_pos + 1) != 0 ) { //tant que lettre à droite
            temp_pos++;
          }
          points += bonusScore(board_pos,temp_word,'G');
        }
        else if ( getIndice(pos).first == getIndice(board_pos + 1).first
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
          while ( getIndice(pos).first == getIndice(temp_pos + 1).first
                  && board->getLetter(temp_pos + 1) != 0 ) { //tant que lettre à droite
            temp_pos++;
          }
          points += bonusScore(board_pos,temp_word,'G');
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
          points += bonusScore(board_pos,temp_word,'H');
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
          points += bonusScore(board_pos,temp_word,'H');
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


void Game::makeMove(const Move & m) {

  unsigned short int board_pos = static_cast<unsigned short int>(m.first_square);
  bool joker;

  if (m.direction == 'H') {  // On joue vers le HAUT
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

  // dans le cas ou la case est vide
  if( b->getLetter(getIndice(x,y)) == 0 ) {
    // dans le cas où la case est adjacente à une case vide
    // directement à gauche (case non vide à droite)
    if( (((y < 14) && ((b->getSpot(getIndice(x,y+1)))->getLetter() == 0))
        || (y >= 14))
        && (y > 0)
        && ((b->getSpot(getIndice(x,y-1)))->getLetter() != 0)) {

          Spot* parcours = b->getSpot(getIndice(x, y-1));
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupère les lettres présentes sur le plateau
          // en avançant simultanément sur le gaddag
          while((parcours->getLetter() != 0)
                && (y - i >= 0) ) {
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = b->getSpot(getIndice(x, y-1-i));
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
    // directement à droite (case non vide à gauche)
    else if( (y < 14)
          && ((b->getSpot(getIndice(x,y+1)))->getLetter() != 0)
          && (((y > 0)
          && ((b->getSpot(getIndice(x,y-1)))->getLetter() == 0))
          || (y <= 0))) {

          std::stack<char> pile;
          Spot* parcours = b->getSpot(getIndice(x, y+1));
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupère les lettres présentes sur le plateau dans une pile
          while((parcours->getLetter() != 0)
                && (y + i <= 14) ) {
            pile.push(parcours->getLetter());
            parcours = b->getSpot(getIndice(x, y+1+i));
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
            && ((b->getSpot(getIndice(x,y+1)))->getLetter() != 0)
            && (y > 0)
            && ((b->getSpot(getIndice(x,y-1)))->getLetter() != 0)){

          Spot* parcours = b->getSpot(getIndice(x, y-1));
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupére la premier mot sur le plateau à l'envers
          // en avançant simultanément sur le gaddag
          while((parcours->getLetter() != 0)
                && (y - i >= 0)){
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = b->getSpot(getIndice(x, y-1-i));
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
              parcours = b->getSpot(getIndice(x,y+1));
              int j = 1;
              // j'avance sur le gaddag avec le deuxième mot présent sur le plateau
              while( gad_coup_possible != nullptr
                    && parcours->getLetter() != 0 ) {
                gad_coup_possible = gad_coup_possible->getNode(parcours->getLetter());
                parcours = b->getSpot(getIndice(x, y+1+j));
                j++;
              }
              // je teste si je forme un mot existant dans le dictionnaire
              if (gad_coup_possible != nullptr
                  && parcours->getLetter() == 0
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

  // dans le cas ou la case est vide
  if (((b->getSpot(getIndice(x,y)))->getLetter() == 0)){
    // dans le cas où la case est adjacente à une case vide
    // directement à gauche (case non vide à droite)
    if( (((x < 14) && ((b->getSpot(getIndice(x+1,y)))->getLetter() == 0))
        || (x >= 14))
        && (x > 0)
        && ((b->getSpot(getIndice(x-1,y)))->getLetter() != 0)) {

          Spot* parcours = b->getSpot(getIndice(x-1, y));
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupère les lettres présentes sur le plateau
          // en avançant simultanément sur le gaddag
          while((parcours->getLetter() != 0)
                && (x - i >= 0) ) {
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = b->getSpot(getIndice(x-1-i, y));
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
    // directement à droite (case non vide à gauche)
    else if( (x < 14)
          && ((b->getSpot(getIndice(x+1,y)))->getLetter() != 0)
          && (((x > 0)
          && ((b->getSpot(getIndice(x-1,y)))->getLetter() == 0))
          || (x <= 0))) {

          std::stack<char> pile;
          Spot* parcours = b->getSpot(getIndice(x+1, y));
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupère les lettres présentes sur le plateau dans une pile
          while((parcours->getLetter() != 0)
                && (x + i <= 14) ) {
            pile.push(parcours->getLetter());
            parcours = b->getSpot(getIndice(x+1+i, y));
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
            && ((b->getSpot(getIndice(x+1,y)))->getLetter() != 0)
            && (x > 0)
            && ((b->getSpot(getIndice(x-1,y)))->getLetter() != 0)){

          Spot* parcours = b->getSpot(getIndice(x-1, y));
          Node* gad_parcours = gad->getFirst();
          int i = 1;
          // je récupére la premier mot sur le plateau à l'envers
          // en avançant simultanément sur le gaddag
          while((parcours->getLetter() != 0)
                && (x - i >= 0)){
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = b->getSpot(getIndice(x-1-i, y));
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
              parcours = b->getSpot(getIndice(x+1,y));
              int j = 1;
              // j'avance sur le gaddag avec le deuxième mot présent sur le plateau
              while( gad_coup_possible != nullptr
                    && parcours->getLetter() != 0 ) {
                gad_coup_possible = gad_coup_possible->getNode(parcours->getLetter());
                parcours = b->getSpot(getIndice(x+1+j, y));
                j++;
              }
              // je teste si je forme un mot existant dans le dictionnaire
              if (gad_coup_possible != nullptr
                  && parcours->getLetter() == 0
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
         Board* b,unsigned short int& points, Move& move,
         unsigned char & j1,
         unsigned char & j2){

  unsigned char x = (getIndice(square)).first;
  unsigned char y = (getIndice(square)).second;
  char letter = (b->getSpot(square))->getLetter();

  //std::cout<<"je rentre dans la fontion Gen"<<std::endl;
  // si la case sur laquelle je me positionne n'est pas vide, j'avance dans
  // le gaddag en lisant la lettre présnte sur la case
  if(letter != 0)
  {
    //std::cout<<"la case contient une lettre "<<std::endl;
    Node* next_arc = arc->getNode(letter);
    GoOn(square, pos,letter, word, rack, next_arc, arc, direction, b, points, move, j1, j2);

  }
  else
  {
    char tab_horizontal[26];
    char tab_vertical[26];
    //std::cout<<"la case ne contient pas de lettre  "<<std::endl;
    // si direction = 1 -> je me déplace horizontalement, et donc les cross sets
    // verticals doivent être des lettres finales
    if(direction == 'H'){
      getCrossSetsHorizontal(square,tab_horizontal, false, b);
      getCrossSetsVertical(square,tab_vertical, true, b);
      /*std::cout<<"le getCrossSetsHorizontal "<<std::endl;
      for (int i = 0; i < 26; i++){
        std::cout<<tab_horizontal[i]<< " ";
      }
      std::cout<<std::endl;
      std::cout<<"le getCrossSetsVertical "<<std::endl;
      for (int i = 0; i < 26; i++){
        std::cout<<tab_vertical[i]<< " ";
      }
      std::cout<<std::endl;*/
    }
    // sinon je me déplace verticalement et donc les cross sets horizontales
    // doivent être des lettres finales
    else
    {
      getCrossSetsHorizontal(square,tab_horizontal, true, b);
      getCrossSetsVertical(square,tab_vertical, false, b);
      /*std::cout<<"le getCrossSetsVertical "<<std::endl;
      for (int i = 0; i < 26; i++){
        std::cout<<tab_vertical[i]<< " ";
      }
      std::cout<<std::endl;
      std::cout<<"le getCrossSetsHorizontal "<<std::endl;
      for (int i = 0; i < 26; i++){
        std::cout<<tab_horizontal[i]<< " ";
      }
      std::cout<<std::endl;*/
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
      /*std::cout<<"je suis à "<< i << "eme case du rack" <<std::endl;
      std::cout<<"le rack contient "<< rack[i]<<std::endl;
      std::cout<<"tab horizontale contitent "<< tab_horizontal[i]<<std::endl;
      std::cout<<"tab_vertical contient  "<< tab_vertical[i]<<std::endl;*/

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
        if (j1 != 255) // Si j1 == 255, cela veut dire qu'on a utilisé aucun joker
          j2 = square; // Je sauvegarde la position du joker
        else
          j1 = square;

        // Je copie la position des jokers pour ne pas la perdre dans les appels
        unsigned char j1_copy2 = j1;
        unsigned char j2_copy2 = j2;

        for(j = 0; j < 26; j++){
          // Je remets les paramètres à leur état initial avant chaque itération
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

          if(tab_horizontal[j] != '/' && tab_vertical[j] != '/'){
            rack[i] = '/'; // Je supprime le joker dans le rack
            Node* next_arc = arc->getNode(j); // J'avance dans le gaddag avec la lettre qu'il représente
            b->getSpot(square)->setLetter('A' + j); // Je place la lettre sur le plateau
            GoOn(square, pos,'A' + j, word, rack, next_arc, arc, direction, b, points,move, j1, j2);
          }
        }
      }
      // Pour chaque lettre que possède le joueur, jouable sur cette case
      // je génère des coups possibles
      else if((rack[i] != '/')
              && (tab_horizontal[rack[i] - 'A'] != '/')
              && (tab_vertical[rack[i] - 'A'] != '/')){
          //std::cout<<"je rentre dans le if pour la lettre "<< i <<std::endl;
          temp = rack[i]; // Je copie la lettre que je joue avant la supprimer
          rack[i] = '/'; // Je supprime la lettre du rack
          Node* next_arc = arc->getNode(temp - 'A'); // J'avance sur le gaddag
          b->getSpot(square)->setLetter(temp); // Je place la lettre sur le plateau
          GoOn(square, pos, temp, word, rack, next_arc, arc, direction, b, points,move, j1, j2);
        }
    }

  }
}


void Game::GoOn(unsigned char  square, int pos, char L,std:: string& word,
          char rack[],Node* new_arc,
          Node* old_arc,unsigned char direction,
          Board* b,unsigned short int& points, Move& move,
          unsigned char & j1,
          unsigned char & j2) {

  unsigned char x = (getIndice(square)).first;
  unsigned char y = (getIndice(square)).second;

  //std::cout<<"je rentre dans la fontion GoOn"<<std::endl;

  if(pos <= 0 ){ // se déplacer à gauche
      //std::cout<<"pos est <= 0 "<<std::endl;
      //std::cout<<"j'ajoute à mon mot la lettre: "<< L << " à gauche"<<std::endl;

      // Je concatène la lettre jouée à gauche du mot
      word = L + word;

      if(new_arc != nullptr){
        //std::cout<<"new_arc n'est pas vide "<<std::endl;
        //j'avance dans le gaddag et le plateau simultanément
        if(direction == 'H'){
          if(y-1 >= 0){
            // je continue à gauche
            unsigned int suivant = getIndice(x,y-1);
            Gen(suivant, pos-1, word, rack, new_arc, direction, b, points, move, j1, j2);
          }

           // Je change de direction
          new_arc = new_arc->getNode('+');
          //std::cout<<"y - 1 = "<< y-1<<std::endl;
          //std::cout<<"y - pos + 1 = "<< y- pos + 1<<std::endl;
          //if(new_arc == nullptr) std::cout<<"new_arc est vide"<<std::endl;

          // Si la nouvelle branche du gaddag n'est pas vide et la case directement
          // à gauche est vide
          if ((new_arc != nullptr)
              && (((y-1>= 0)
              && ((b->getSpot(getIndice(x,y-1)))->getLetter() == 0))
              || (y-1 < 0))){

                // Si la branche est finale, et qu'il n'y a pas de case non vide
                // à droite j'enregistre un coup possible
                if((new_arc->isFinal())
                  && ((y-pos+1 >14) || ((y-pos+1 <=14)
                  && ((b->getSpot(getIndice(x,y-pos+1)))->getLetter() == 0)))){

                    Move new_move (word,getIndice(x, y),'D', j1, j2);
                    //std::cout << "Dun coup possible " << word << " à partir de " << getIndice(x, y)
                    //        << " ; qui donne : " << std::flush;
                    //std::cout << "j1  : " <<static_cast<int>(j1) << std::endl;
                    //std::cout << "j2  : " <<static_cast<int>(j2) << std::endl;

                    // Appel de la fonction qui calcule le score
                    unsigned short int new_points = score(new_move);
                    //std::cout << points <<  " points" << std::endl;

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

          if(x-1 >= 0){
            unsigned int suivant = getIndice(x-1,y);
            Gen(suivant, pos-1, word, rack, new_arc, direction, b, points, move, j1, j2);
          }

          new_arc = new_arc->getNode('+');
          //std::cout<<"x - 1 = "<< x-1<<std::endl;
          //std::cout<<"x - pos + 1 = "<< x - pos + 1<<std::endl;
          //if(new_arc == nullptr) std::cout<<"new_arc est vide"<<std::endl;
          if ((new_arc != nullptr)
              && (((x-1 >= 0)
              && ((b->getSpot(getIndice(x-1,y)))->getLetter() == 0))
              || (x-1 < 0))){

                if((new_arc->isFinal())
                  && ((x-pos+1 >14) || ((x-pos+1 <=14)
                  && ((b->getSpot(getIndice(x-pos+1,y)))->getLetter() == 0)))){

                    Move new_move(word,getIndice(x, y),'B', j1, j2);
                    //std::cout << "Bun coup possible " << word
                    //        << " ; qui donne : " << std::flush;
                    //std::cout << "j1  : " <<static_cast<int>(j1) << std::endl;
                    //std::cout << "j2  : " <<static_cast<int>(j2) << std::endl;
                    unsigned short int new_points = score(new_move); // = l'appel récursif
                    //std::cout << new_points <<  " points" << std::endl;
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
    //std::cout<<"pos est > 0 "<<std::endl;
    //std::cout<<"j'ajoute à mon mot la lettre: "<< L << " à droite"<<std::endl;

    // Je concatène la lettre jouée à gauche du mot
    word = word + L;

    if((new_arc != nullptr) && (new_arc->isFinal())){
      //std::cout<<"je rentre avec la lettre "<< L <<" et elle est finale" <<std::endl;

      // Si la branche est finale , et qu'il n'y a pas de case non vide
      // directement à droite, j'enregistre un coup possible
      if(direction == 'H'){ // Horizontalement

        if (((y + 1 <= 14)
            && ((b->getSpot(getIndice(x,y+1)))->getLetter() == 0))
            ||(y + 1 > 14)){

              Move new_move (word,square,'G', j1, j2);
              //std::cout << "Gun coup possible " << word << " à partir de " << getIndice(x, y)
              //          << " ; qui donne : " << std::flush;
              //std::cout << "j1  : " <<static_cast<int>(j1) << std::endl;
              //std::cout << "j2  : " <<static_cast<int>(j2) << std::endl;

              // Appel de la fonction qui calcule le score
              unsigned short int new_points = score(new_move); // = l'appel récursif
              //std::cout << new_points <<  " points" << std::endl;

              // Si le score calculé est meilleur, on garde le dernier coup
              if (new_points > points){
                move = new_move;
                points = new_points;
              }
        }
      }
      else { // verticalement
        if (((x + 1 <= 14)
            && ((b->getSpot(getIndice(x + 1,y)))->getLetter() == 0))
            ||(x + 1 > 14)){

              Move new_move = Move (word,getIndice(x, y),'H', j1, j2);
              //std::cout << "Hun coup possible " << word
              //          << " ; qui donne : " << std::flush;
              //std::cout << "j1  : " <<static_cast<int>(j1) << std::endl;
              //std::cout << "j2  : " <<static_cast<int>(j2) << std::endl;

              // Appel de la fonction qui calcule le score
              unsigned short int new_points = score(new_move); // = l'appel récursif
              //std::cout << new_points <<  " points" << std::endl;

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
  std::cout << "Score : " << player->getPoints() << std::endl << std::endl;
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
  unsigned short int s = 0;
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

  // Si le meilleur coup rapporte un score nul, cela veut dire que la partie est terminée
  if(s == 0){
    ended = true;
  }

  std::cout<<"le meilleur coup est "<<m.word
            << " et ça raporte "<<s <<" points, jouable à partir de la case "
            <<static_cast<int>(m.first_square)<<" vers "<<m.direction<<std::endl;

  player->addPoints(s); // Ajouter les points rapportées par le coup au score
  makeMove(m); // Jouer le mot sur le plateau
  //draw(); // Attribuer des lettres au joueur

}


void Game::finalPrint() const {
  if (ended && bag->isEmpty()) {
    std::cout << "Le joueur ne peut plus jouer et le sac et vide."
              << std::endl;
  }
  else {
    std::cout << "Le joueur est bloqué ! (nul...)"
              << std::endl;
    printBag();
  }
  std::cout << "Partie terminée..." << std::endl
            << "Le joueur termine avec un score de "
            << player->getPoints() << std::endl;
}





























void Game::attribueLettre(const std::string & s) {
  unsigned int i = 0;
  unsigned int size = s.size();

  for (i = 0; i < size; i++) {
    player->setLetter(i,s[i]);
  }

  while (i < 7) {
    player->removeLetterIndice(i);
    i++;
  }

}
