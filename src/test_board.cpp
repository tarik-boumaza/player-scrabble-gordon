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

  ss << ".LPHABETIQUE..." << std::endl ;
  ss << "L.............." << std::endl ;
  ss << "P.............." << std::endl ;
  ss << "H.............." << std::endl ;
  ss << "A.............." << std::endl ;
  ss << ".ETISE........." << std::endl ;
  ss << "E.............." << std::endl ;
  ss << "T...PROJET....." << std::endl ;
  ss << "I......O......." << std::endl ;
  ss << "Q......U......." << std::endl ;
  ss << "U......E......." << std::endl ;
  ss << "E......U......." << std::endl ;
  ss << ".....SCRABBLE.." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;

  g.board->load(ss) ;
  std::cout <<*(g.board)<< std::endl ;
  g.moveTurn();

  //std::cout <<*(g.board)<< std::endl ;




  return 0 ;
}
