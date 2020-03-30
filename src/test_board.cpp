#include "board.hpp"
#include "game.hpp"
#include "gaddag.hpp"
#include "player.hpp"

#include <iostream>
#include <sstream>

#include <list>

int main() {
  Game g;
  g.init();

  std::stringstream ss ;

  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "...T..........." << std::endl ;
  ss << "...R...T......." << std::endl ;
  ss << "...E...E....P.." << std::endl ;
  ss << "...M...L....O.." << std::endl ;
  ss << "...BAFRES...U.." << std::endl ;
  ss << "...L...P....D.." << std::endl ;
  ss << "...E...O....R.." << std::endl ;
  ss << "...S...R....I.." << std::endl ;
  ss << ".......T....N.J" << std::endl ;
  ss << ".......AZURASSE" << std::endl ;
  ss << "..............U" << std::endl ;
  ss << "..............N" << std::endl ;

  g.board->load(ss) ;
  std::cout <<*(g.board)<< std::endl ;

  std::string word;
  char table[7];

  for (unsigned short int i = 0; i < 7; i++) {
    table[i] = g.player->getLetter(i);
  }

  Node * parcours = g.gad->getFirst();
  Board b(*(g.board));
  unsigned short int s = 0;
  Move m;

  //g.Gen(223,0,word,table,parcours,1,&b,s,m);
  g.moveTurn();
  //std::cout <<*(g.board)<< std::endl ;

  //std::cout <<*(g.board)<< std::endl ;




  return 0 ;
}
