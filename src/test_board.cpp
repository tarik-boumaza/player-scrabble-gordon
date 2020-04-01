#include "board.hpp"
#include "bag.hpp"
#include "game.hpp"
#include "gaddag.hpp"
#include "player.hpp"

#include <iostream>
#include <sstream>

#include <list>

int main() {
  Bag * b = new Bag("data/letters.txt","data/points.txt");
  b->printPoints();
  /*std::stringstream ss ;

  ss << "F.............." << std::endl ;
  ss << "I....WAPS......" << std::endl ;
  ss << "N......I......." << std::endl ;
  ss << "I......FIQHS..." << std::endl ;
  ss << "ES..ME.A..OUIE." << std::endl ;
  ss << ".H.POU.M......." << std::endl ;
  ss << "DOTAL.BEY......" << std::endl ;
  ss << ".NOVERAS......." << std::endl ;
  ss << ".ACE..R........" << std::endl ;
  ss << ".S.R..D........" << std::endl ;
  ss << "..NACREZ......." << std::endl ;
  ss << "..AI..N........" << std::endl ;
  ss << "..VS..T........" << std::endl ;
  ss << ".JE............" << std::endl ;
  ss << "GELEE.........." << std::endl ;

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
  Move m("MALT",82,'D');

  //g.Gen(223,0,word,table,parcours,1,&b,s,m);
  g.moveTurn();
  g.makeMove(m);

  std::cout <<*(g.board)<< std::endl ;*/




  return 0 ;
}
