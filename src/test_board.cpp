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


  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << ".........G....." << std::endl ;
  ss << "........LOS...." << std::endl ;
  ss << "........IDE...." << std::endl ;
  ss << "........TEX...." << std::endl ;
  ss << ".......US.I...." << std::endl ;
  ss << "CILS...N..E...." << std::endl ;
  ss << "...EMBOIREZ...." << std::endl ;
  ss << "......MEUH....." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;

  ss << "..............." << std::endl ;
  ss << "GENTIL........." << std::endl ;
  ss << "..O............" << std::endl ;
  ss << "..T............" << std::endl ;
  ss << "..E............" << std::endl ;
  ss << "..S............" << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;



  bo->load(ss2);
  std::cout << *bo << std::endl;*/



  std::stringstream ss ;

  ss << ".......B.EFFARA" << std::endl ;
  ss << ".....AGIS..E..U." << std::endl ;
  ss << ".....N.P.G.D..N" << std::endl ;
  ss << "...Q.N.ALOSE..E" << std::endl ;
  ss << "...U.I..IDES..." << std::endl ;
  ss << "S.ME.VU.TEX...." << std::endl ;
  ss << "I.E...DUS.I...." << std::endl ;
  ss << "CILS...N..EPURE" << std::endl ;
  ss << ".N.EMBOIREZ...U" << std::endl ;
  ss << ".H.R..MEUH....T" << std::endl ;
  ss << ".A.O..........." << std::endl ;
  ss << ".L.N..........." << std::endl ;
  ss << "WATT..........." << std::endl ;
  ss << "ET............." << std::endl ;
  ss << "B.............." << std::endl ;

  g.board->load(ss) ;
  Board b(*(g.board));


  /*Move m ("ALPHABETIQUE",0,'B');
  unsigned short int s = g.score(m,0);
  std::cout << std::endl << "Score final : " << s << std::endl;
  */

  g.attribueLettre("OOATOIV");
  g.print();
  std::cout << "appel à moveTurn" << std::endl;
  g.moveTurn();
  g.print();


  /*char table[7];
  for(int i=0; i < 7; i++){
    table[i] = '/';
  }
  table[0]= 'T';
  table[1]= 'R';
  table[2]= 'M';
  table[3]= 'H';
  table[4]= 'T';
  table[5]= 'I';
  table[6]= '*';

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
