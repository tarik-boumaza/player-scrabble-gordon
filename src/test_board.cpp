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
  ss << "ALPHABETIQUE..." << std::endl ;
  ss << "L.............." << std::endl ;
  ss << "P.............." << std::endl ;
  ss << "H.............." << std::endl ;
  ss << "A.............." << std::endl ;
  ss << "..............." << std::endl ;
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

  Board b(*(g.board));

  std::cout <<*(g.board)<< std::endl ;
  //std::cout << b << std::endl ;
  //std::cout << "Tarikounet mégnon" << std::endl ;
  //std::list<unsigned char> tab (b.getAnchorSquares());



  //////////////////////
  /*while(!tab.empty()) {
    i = tab.back();
    j++;
    //std::cout << static_cast<int>(i) / 15 <<","<< static_cast<int>(i) % 15 << std::endl;
    std::cout<< static_cast<int>(i) <<std::endl;
    tab.pop_back();

  }*/
  //////////////////////


  unsigned int table[26];
  //g.getCrossSetsHorizontal(115,table,true);
  for(unsigned int i =0; i<26;i++){
    table[i] = 0;
  }
  table[0] = 1;
  table[1]=1;
  table[18] = 2;
  table[4]=1;
  std::cout<<std::endl;
  std::string word = "";
  Node* parcours = g.gad->getFirst();
  g.Gen(115,0,word,table,parcours,1,&b);
  std::cout<<word<<std::endl;
  //std::cout <<*(g.board)<< std::endl ;
  //std::cout<<"j'ai "<< j <<" anchor_squares"<<std::endl;
  //g.board->getSpot(0)->setLetter('H');

  ////////////////////
  /*if(g.board->getSpot(130)->getLetter() == 0)
  std::cout << "la case est libre" << std::endl ;*/
  ////////////////////

  return 0 ;
}
