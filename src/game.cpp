#include <iostream>
#include "map.hpp"
#include "board.hpp"
#include "player.hpp"
#include "bag.hpp"
#include "gaddag.hpp"
#include "game.hpp"
#include <stack>



Game::Game() {
  bag = new Bag("./data/letters.txt","./data/points.txt");
  player = new Player;
  gad = new Gaddag;
  board = new Board;
}


Game::~Game() {
  delete board;
  delete player;
  delete bag;
  delete gad;
}


void Game::draw(const unsigned short int & n) {
  unsigned int i = 0;
  while (i < n && !isFinished() ) {
    player->setLetter(bag->randomDraw());
    i++;
  }
}


void Game::init() {
  draw(7);
  gad->addDictionnary();
}


void Game::printDico() {
  gad->print();
}


void Game::printHand() const {
  player->printHand();
}


void Game::printBag() const {
  bag->printLetters();
}


bool Game::isFinished() const {
  return bag->isEmpty();
}


void Game::useLetter(const char & c) {
  player->removeLetter(c);
}


//c.first représente la case du plateau
//c.second représente la lettre jouée sur la case
couple Game::score (const couple & c) const {
  unsigned short int res = bag->getPoints(c.second);
  res *= static_cast<unsigned short int>(board->getLetterFactor(c.first));
  couple p (res,static_cast<unsigned short int>(board->getWordFactor(c.first)));
  return p;
  //p.first est le score que donne la lettre multiplié par le letter_factor
  //p.second est le word_factor
}


//couple.first représente la case du plateau
//couple.second représente la lettre jouée sur la case
//l contient ainsi l'ensemble des lettres jouées ainsi que leurs positions
unsigned short int Game::score(const std::list<couple> & l) const {
  unsigned short int res = 0;
  unsigned short int wf = 1;
  std::list<couple> copy (l);
  couple temp;
  while(!copy.empty()) {
    temp = score(copy.back()); //temp.first est le score, temp.second est le word_factor
    res += temp.first;
    if (temp.second > wf)
      wf = temp.second;
    copy.pop_back();
  }
  return (wf * res);
}


void Game::getCrossSetsHorizontal(const unsigned char & square,
                                  char tab_horizontal[]) {
  unsigned char x = (board->getIndice(square)).first;
  unsigned char y = (board->getIndice(square)).second;

  // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
  // à gauche
  if(((board->getSpot(board->getIndice(x,y)))->getLetter() == 0)){
    if( (((y < 14) && ((board->getSpot(board->getIndice(x,y+1)))->getLetter() == 0))
        || (y >= 14))
        && (y > 0)
        && ((board->getSpot(board->getIndice(x,y-1)))->getLetter() != 0)) {

          Spot* parcours = board->getSpot(board->getIndice(x, y-1));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (y - i >= 0) ) {
            std::cout<<"la lettre est "<<parcours->getLetter()<<std::endl;
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x, y-1-i));
            i++;
          }

          if(gad_parcours != nullptr)
            gad_parcours = gad_parcours->getNode('+');

          for(int i = 0; i < 26; i++) {
            if(gad_parcours->getNode(i) != nullptr){
              tab_horizontal[i] = gad->getLetter(i);
            }
            else
            {
              tab_horizontal[i] = '/';
            }
          }

    }

    // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
    // à droite
    else if( (y < 14)
          && ((board->getSpot(board->getIndice(x,y+1)))->getLetter() != 0)
          && (((y > 0)
          && ((board->getSpot(board->getIndice(x,y-1)))->getLetter() == 0))
          || (y <= 0))) {

          std::cout<<"je rentre dans le deuxième cas"<<std::endl;
          std::stack<char> pile;
          Spot* parcours = board->getSpot(board->getIndice(x, y+1));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (y + i >= 0) ) {
            pile.push(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x, y+1+i));
            i++;
          }

          while (!pile.empty()) {
            gad_parcours = gad_parcours->getNode(pile.top());
            pile.pop();
          }

          for(int i = 0; i < 26; i++) {
            if(gad_parcours->getNode(i) != nullptr){
              tab_horizontal[i] = gad->getLetter(i);
            }
            else
            {
              tab_horizontal[i] = '/';
            }
          }
    }

    else if ((y < 14)
            && ((board->getSpot(board->getIndice(x,y+1)))->getLetter() != 0)
            && (y > 0)
            && ((board->getSpot(board->getIndice(x,y-1)))->getLetter() != 0)){

          Spot* parcours = board->getSpot(board->getIndice(x, y-1));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (y - i >= 0)){
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x, y-1-i));
            i++;
          }

          gad_parcours = gad_parcours->getNode('+');
          Node * copy = gad_parcours;

          for (int i = 0; i < 26; i++) {

            copy = gad_parcours;

            if (copy->getNode(i) != nullptr) {

              copy = copy->getNode(i);
              Node* gad_coup_possible = copy;
              parcours = board->getSpot(board->getIndice(x,y+1));
              int j = 1;

              while( gad_coup_possible != nullptr
                    && parcours->getLetter() != 0 ) {
                gad_coup_possible = gad_coup_possible->getNode(parcours->getLetter());
                parcours = board->getSpot(board->getIndice(x, y+1+j));
                j++;
              }

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
    {
      for(int i = 0; i < 26; i++){
        tab_horizontal[i] = gad->getLetter(i);
      }
    }

  }
  else
  {
    for(int i = 0; i < 26; i++){
      tab_horizontal[i] = '/';
    }
  }

}

void Game::getCrossSetsVertical(const unsigned char & square,
                                  char tab_horizontal[]) {
  unsigned char x = (board->getIndice(square)).first;
  unsigned char y = (board->getIndice(square)).second;

  // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
  // à gauche
  if (((board->getSpot(board->getIndice(x,y)))->getLetter() == 0)){
    if( (((x < 14) && ((board->getSpot(board->getIndice(x+1,y)))->getLetter() == 0))
        || (x >= 14))
        && (x > 0)
        && ((board->getSpot(board->getIndice(x-1,y)))->getLetter() != 0)) {

          Spot* parcours = board->getSpot(board->getIndice(x-1, y));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (x - i >= 0) ) {
            std::cout<<"la lettre est "<<parcours->getLetter()<<std::endl;
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x-1-i, y));
            i++;
          }

          if(gad_parcours != nullptr)
            gad_parcours = gad_parcours->getNode('+');

          for(int i = 0; i < 26; i++) {

            if(gad_parcours->getNode(i) != nullptr){
              tab_horizontal[i] = gad->getLetter(i);
            }
            else
            {
              tab_horizontal[i] = '/';
            }
          }
    }

        // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
        // à droite
    else if( (x < 14)
          && ((board->getSpot(board->getIndice(x+1,y)))->getLetter() != 0)
          && (((x > 0)
          && ((board->getSpot(board->getIndice(x-1,y)))->getLetter() == 0))
          || (x <= 0))) {

          std::cout<<"je rentre dans le deuxième cas"<<std::endl;
          std::stack<char> pile;
          Spot* parcours = board->getSpot(board->getIndice(x+1, y));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (x + i >= 0) ) {
            pile.push(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x+1+i, y));
            i++;
          }

          while (!pile.empty()) {
            gad_parcours = gad_parcours->getNode(pile.top());
            pile.pop();
          }

          for(int i = 0; i < 26; i++) {
            if(gad_parcours->getNode(i) != nullptr){
              tab_horizontal[i] = gad->getLetter(i);
            }
            else
            {
              tab_horizontal[i] = '/';
            }
          }
    }

    else if ((x < 14)
            && ((board->getSpot(board->getIndice(x+1,y)))->getLetter() != 0)
            && (x > 0)
            && ((board->getSpot(board->getIndice(x-1,y)))->getLetter() != 0)){

          Spot* parcours = board->getSpot(board->getIndice(x-1, y));
          Node* gad_parcours = gad->getFirst();
          int i = 1;

          while((parcours->getLetter() != 0)
                && (x - i >= 0)){
            gad_parcours = gad_parcours->getNode(parcours->getLetter());
            parcours = board->getSpot(board->getIndice(x-1-i, y));
            i++;
          }

          gad_parcours = gad_parcours->getNode('+');
          Node * copy = gad_parcours;

          for (int i = 0; i < 26; i++) {

            copy = gad_parcours;

            if (copy->getNode(i) != nullptr) {

              copy = copy->getNode(i);
              Node* gad_coup_possible = copy;
              parcours = board->getSpot(board->getIndice(x+1,y));
              int j = 1;

              while( gad_coup_possible != nullptr
                    && parcours->getLetter() != 0 ) {
                gad_coup_possible = gad_coup_possible->getNode(parcours->getLetter());
                parcours = board->getSpot(board->getIndice(x+1+j, y));
                j++;
              }

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
    {
      for(int i = 0; i < 26; i++){
        tab_horizontal[i] = gad->getLetter(i);
      }
    }

  }
  else
  {
    for(int i = 0; i < 26; i++){
      tab_horizontal[i] = '/';
    }
  }
}
