#include <iostream>
#include "board.hpp"
#include "player.hpp"
#include "bag.hpp"
#include "gaddag.hpp"
#include "game.hpp"


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

void Game::getCrossSetsHorizontal(const unsigned char & square, char tab_horizontal[]){
  unsigned char x = board->getIndice(square).first;
  unsigned char y = board->getIndice(square).second;

  // dans le cas où ma case n'est adjacente qu'à une seule case vide directement
  // à gauche
  if((x < 14) && (board->getSpot(board->getIndice(x+1,y)).getLetter() == 0) &&
      (x > 0) && (board->getSpot(board->getIndice(x-1,y)).getLetter() != 0)){
        Spot parcours = board->getSpot(board->getIndice(x-1,y));
        Node* gad_parcours = gad->getFirst();
        int i = 1;
        while(parcours.getLetter() != 0){
          gad->letterForward(gad_parcours,parcours.getLetter());
          parcours = board->getSpot(board->getIndice(x-1-i,y));
          i++;
        }
        gad->letterForward(gad_parcours,'+');
        for(int i = 0; i < 27; i++){
          Node* res = gad_parcours->tab[i] ;
          if(res != nullptr){
            tab_horizontal[i] = gad->getLetter(i);
          }
          else{
            tab_horizontal[i] = '/';
          }
        }
      }



}
