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

  /*Board * bo = new Board;

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
  std::cout << *bo << std::endl;*/

  std::stringstream ss ;

  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "....M.........." << std::endl ;
  ss << "....O.........." << std::endl ;
  ss << "....L.V........" << std::endl ;
  ss << "...KYRIES......" << std::endl ;
  ss << "...ES.N........" << std::endl ;
  ss << "...T..G........" << std::endl ;
  ss << "...J..TO......." << std::endl ;
  ss << "...E...C......." << std::endl ;
  ss << ".......U......." << std::endl ;
  ss << ".......L......." << std::endl ;
  ss << ".......E......." << std::endl ;
  g.board->load(ss) ;

  Board b(*(g.board));
  //g.attribueLettre("A");
  //g.print();


  /*Move m ("ALPHABETIQUE",0,'B');
  unsigned short int s = g.score(m,0);
  std::cout << std::endl << "Score final : " << s << std::endl;
  */

  g.print();
  g.moveTurn();
  g.print();

  /*
  char table[7];
  for(int i=0; i < 7; i++){
    table[i] = '/';
  }
  table[3]='*';
  table[4] = '*';
  Node* arc = g.gad->getFirst();
  Move m("",0,'B',255,255);
  unsigned char j1 = 255, j2=255;
  unsigned short int s = 0;
  std::string word;



  g.Gen(180,0,word,table,arc,0,&b,s,m,j1,j2);
  std::cout <<" move " << m.word << std::endl;
  std::cout <<" j1 " <<static_cast<int> (m.j1) << std::endl;
  std::cout <<" j2 " <<static_cast<int>(m.j2) << std::endl;

  g.makeMove(m);

  std::cout << *(g.board) << std::endl;


*/








  return 0 ;
}
