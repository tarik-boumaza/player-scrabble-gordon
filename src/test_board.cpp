#include "board.hpp"
#include "game.hpp"
#include "gaddag.hpp"

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
  ss << "...E...E.WHIPS." << std::endl ;
  ss << "...M...L....O.." << std::endl ;
  ss << "...BAFRES..FUSE" << std::endl ;
  ss << "...L...P..FADES" << std::endl ;
  ss << "...E...O....R.." << std::endl ;
  ss << "...S...R....I.." << std::endl ;
  ss << ".......T....N.J" << std::endl ;
  ss << ".......AZURASSE" << std::endl ;
  ss << "....FLET......U" << std::endl ;
  ss << "OBERA.........N" << std::endl ;

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

  g.Gen(195,0,word,table,parcours,1,&b,s,m);
  //g.moveTurn();
  //std::cout <<*(g.board)<< std::endl ;

  //std::cout <<*(g.board)<< std::endl ;




  return 0 ;
}
