#include "board.hpp"

#include <iostream>
#include <sstream>

#include <list>


int main() {
  Board b ;

  //std::cout << b << std::endl ;

  std::stringstream ss ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "....PROJET....." << std::endl ;
  ss << ".......O......." << std::endl ;
  ss << ".......U......." << std::endl ;
  ss << ".......E......." << std::endl ;
  ss << ".......U......." << std::endl ;
  ss << ".....SCRABBLE.." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;

  b.load(ss) ;

  std::cout << b << std::endl ;
  std::list<unsigned char> tab (b.getAnchorSquares());
  unsigned char i;
  int j = 0;
  while(!tab.empty()) {
    i = tab.back();
    j++;
    std::cout << static_cast<int>(i) / 15 <<","<< static_cast<int>(i) % 15 << std::endl;
    tab.pop_back();

  }
  std::cout<<"j'ai "<< j <<" anchor_squares"<<std::endl;
  //b.spots[0].setLetter('H');
  //std::cout << b << std::endl ;

  return 0 ;
}
