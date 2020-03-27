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
  std::cout <<*(g.board)<< std::endl ;


  unsigned int table[26];
  for(unsigned int i =0; i<26;i++){
    table[i] = 0;
  }
  table[0] = 1;
  table[1]=1;
  table[18] = 2;
  table[11] = 1;
  table[12] = 1;
  table[19] = 1;
  table[4]=1;

  std::cout<<std::endl;
  std::string word = "";
  Board b(*(g.board));

  Node* parcours = g.gad->getFirst();
  Move m;

  m.word = "";
  m.first_square = 0;
  m.direction = 'H';

  unsigned short int s = 0;
  g.Gen(115,0,word,table,parcours,1,&b,s,m);

  //std::cout<<"le coup possible est "<<m.word<<std::endl;


  return 0 ;
}
