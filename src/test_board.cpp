#include "board.hpp"
#include "bag.hpp"
#include "game.hpp"
#include "gaddag.hpp"
#include "player.hpp"

#include <iostream>
#include <sstream>

#include <list>

int main() {

 

  Bag * bag = new Bag ("./data/letters.txt","./data/points.txt");
  bag->printPoints();

  Game g;
  g.init();

  Board * bo = new Board;

  std::stringstream ss2 ;

  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;

  bo->load(ss2);
  std::cout << *bo << std::endl;

  std::stringstream ss ;

  ss << ".LPHABETIQUE..." << std::endl ;
  ss << "H.............." << std::endl ;
  ss << "P.............." << std::endl ;
  ss << "H.............." << std::endl ;
  ss << "A.............." << std::endl ;
  ss << ".ETISE........." << std::endl ;
  ss << "E.............." << std::endl ;
  ss << "T.............." << std::endl ;
  ss << "I.............." << std::endl ;
  ss << "Q.............." << std::endl ;
  ss << "U.............." << std::endl ;
  ss << "E.............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  g.board->load(ss) ;


  //g.attribueLettre("A");
  g.print();


  Move m ("ALPHABETIQUE",0,'B');
  unsigned short int s = g.score(m,0);
  std::cout << std::endl << "Score final : " << s << std::endl;
  

  //g.moveTurn();
  g.print();
  




  return 0 ;
}
