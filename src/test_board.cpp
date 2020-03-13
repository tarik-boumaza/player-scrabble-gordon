#include "board.hpp"
#include "game.hpp"

#include <iostream>
#include <sstream>

#include <list>


int main() {
  Game g;
  //Board b ;

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

  g.board->load(ss) ;

  std::cout <<*(g.board)<< std::endl ;
  //std::list<unsigned char> tab (b.getAnchorSquares());
  unsigned char i;
  int j = 0;
  /*while(!tab.empty()) {
    i = tab.back();
    j++;
    //std::cout << static_cast<int>(i) / 15 <<","<< static_cast<int>(i) % 15 << std::endl;
    std::cout<< static_cast<int>(i) <<std::endl;
    tab.pop_back();

  }*/

  char table[27];
  g.getCrossSetsHorizontal(115,table);
  for(int i =0; i<27;i++){
    std::cout<<table[i]<<" ";
  }
  std::cout<<std::endl;
  //std::cout<<"j'ai "<< j <<" anchor_squares"<<std::endl;
  //g.board->getSpot(0)->setLetter('H');
  /*if(g.board->getSpot(130)->getLetter() == 0)
  std::cout << "la case est libre" << std::endl ;*/

  return 0 ;
}
