#include "board.hpp"
#include "bag.hpp"
#include "game.hpp"
#include "gaddag.hpp"
#include "player.hpp"

#include <iostream>
#include <sstream>

#include <list>


int main() {


  //Bag * bag = new Bag ();
  //bag->printPoints();

  Game g;
  g.init();

  std::stringstream ss ;


  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ; ///
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;



  g.board->load(ss) ;
  Board b(*(g.board));

  g.attribueLettre("ARMETIS");

  //g.board->spots[].setLetter('',true);
  //g.board->spots[].setLetter('',true);



  g.print();
  g.moveTurn();
  std::cout << std::endl << std::endl << std::endl;
  g.print();



/*
  std::cout << *g.board << std::endl << std::endl;
  Move m ("MOT",0,'D',255,255);
  unsigned short int s = g.score(m);
  g.makeMove(m);
  std::cout << *g.board << std::endl << std::endl;
  std::cout << std::endl << "Points marqués : " << s << std::endl;
*/



  return 0;

}