#include "board.hpp"
#include "game.hpp"
#include "gaddag.hpp"

#include <iostream>
#include <sstream>

#include <list>


int main() {
  Game g;
  g.init();

  Board * b_vierge = new Board;
  std::stringstream ss2;
  ss2 << "................" << std::endl ;
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

  b_vierge->load(ss2);
  std::cout << *b_vierge << std::endl << std::endl;





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


  unsigned int table[26];
  for(unsigned int i =0; i<26;i++){
    table[i] = 0;
  }
  table['R' - 'A']++ ;
  table['B' - 'A']++ ;
  table['E' - 'A']++ ;
  table['T' - 'A']++ ;
  table['A' - 'A']++ ;
  table['Z' - 'A']++ ;
  table['W' - 'A']++;

  std::cout<<std::endl;
  std::string word = "";
  Board b(*(g.board));


  Move m ("",0,'H');
  unsigned short int s = 0;
  Node* parcours = g.gad->getFirst();

  g.Gen(b_vierge->getIndice(12,0),0,word,table,parcours,0,&b,s,m);

  std::cout << std::endl << "Le meilleur coup possible est : " << m.word
            << ", il rapporte " << s << " points" << std::endl << std::endl;


  std::cout << "Je sais que le meilleur coup donne : "
            << g.score(Move("ALPHABETIQUE",0,'B')) << " points " << std::endl;


  return 0 ;
}
