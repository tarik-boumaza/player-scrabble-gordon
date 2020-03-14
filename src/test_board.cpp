#include "board.hpp"
#include "game.hpp"

#include <iostream>
#include <sstream>

#include <list>


int main() {
  Game g;
  g.init();
  //Board b ;

  //std::cout << b << std::endl ;

  std::stringstream ss ;
  ss << "..............." << std::endl ;
  ss << ".QUE.CONQUE...." << std::endl ;
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

  char table_h[26];
  char table_v[26];
  g.getCrossSets(19,table_h,table_v);
  std::cout << "CROSS SET HORIZONTAL" << std::endl;
  for(int i =0; i<26;i++){
    std::cout<<table_h[i]<<" ";
  }
  std::cout<<std::endl;
  std::cout << "CROSS SET VERTICAL" << std::endl;
  for(int i =0; i<26;i++){
    std::cout<<table_v[i]<<" ";
  }
  std::cout<<std::endl;
  //std::cout<<"j'ai "<< j <<" anchor_squares"<<std::endl;
  //g.board->getSpot(0)->setLetter('H');
  /*if(g.board->getSpot(130)->getLetter() == 0)
  std::cout << "la case est libre" << std::endl ;*/

  return 0 ;
}
