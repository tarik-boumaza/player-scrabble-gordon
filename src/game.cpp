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


void Game::init() {
  for (unsigned int i = 0;  i < 7; i++) {
    player->setLetter(i,bag->randomDraw());
  }
  gad->addDictionnary();
}


void Game::printDico() {
  gad->print();
}


void Game::printHands() const {
  player->printHand();
}


void Game::printBag() const {
  bag->printLetters();
}


void Game::draw() {
  unsigned int i = 0;
  while (i < 7 && !isFinished() ) {
    if (player->getLetter(i) == '/')
      player->setLetter(i,bag->randomDraw());
    i++;
  }
}


bool Game::isFinished() const {
  return bag->isEmpty();
}


void Game::useLetter(const std::list<unsigned int> & l) {
  std::list<unsigned int> copy(l);
  while(!copy.empty()) {
    player->setLetter(copy.back(),'/');
    copy.pop_back();
  }
}


std::pair<unsigned short int, unsigned short int> Game::score
                          (const unsigned char & pos, const unsigned char & l) const {
  unsigned short int res = bag->getPoints(l);
  res *= board->getLetterFactor(pos);
  std::pair<unsigned short int, unsigned short int> p (res,board->getWordFactor(pos));
  return p;
}


void Game::getCrossSetsHorizontal(const unsigned char & square,
                                  char tab_horizontal[]) {
  unsigned char x = (board->getIndice(square)).first;
  unsigned char y = (board->getIndice(square)).second;

  // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
  // à gauche

  if( (((y < 14) && ((board->getSpot(board->getIndice(x,y+1)))->getLetter() == 0))
      || (y >= 14))
      && (y > 0)
      && ((board->getSpot(board->getIndice(x,y-1)))->getLetter() != 0)) {
        Spot* parcours = board->getSpot(board->getIndice(x, y-1));
        Node* gad_parcours = gad->getFirst();
        int i = 1;
        while(parcours->getLetter() != 0) {

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
          else{
            tab_horizontal[i] = '/';
          }
        }
      }

      // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
      // à droite
      if( (y < 14)
          && ((board->getSpot(board->getIndice(x,y+1)))->getLetter() != 0)
          && (((y > 0) && ((board->getSpot(board->getIndice(x,y-1)))->getLetter() == 0))
          || (y <= 0))) {
            std::stack<char> pile;
            Spot* parcours = board->getSpot(board->getIndice(x, y+1));
            Node* gad_parcours = gad->getFirst();
            int i = 1;
            while(parcours->getLetter() != 0) {
              pile.push(parcours->getLetter());
              parcours = board->getSpot(board->getIndice(x, y+1+i));
              i++;
            }

            while (!pile.empty()) {
              gad_parcours = gad_parcours->getNode(pile.top());
              pile.pop();
            }

            if(gad_parcours == nullptr)
              std::cout<<"gad_parcours est vide"<<std::endl;
            for(int i = 0; i < 26; i++) {
              if(gad_parcours->getNode(i) != nullptr){
                tab_horizontal[i] = gad->getLetter(i);
              }
              else{
                tab_horizontal[i] = '/';
              }
            }
          }

      else{

        Spot* parcours = board->getSpot(board->getIndice(x, y-1));
        Node* gad_parcours = gad->getFirst();
        int i = 1;
        while((parcours->getLetter() != 0) && (y - i >= 0)){

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
            else {
              tab_horizontal[i] = '/';
            }
          }
          else {
              tab_horizontal[i] = '/';
          }
        }

      }
      
}
