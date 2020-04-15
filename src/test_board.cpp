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
  ss << "...DIOLAS......" << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;

  ss << ".......B.EFFARA" << std::endl ;
  ss << ".L..VAGIS..E..U" << std::endl ;
  ss << "OYE..N.P.G.D..N" << std::endl ;
  ss << ".C.Q.N.ALOSE..E" << std::endl ;
  ss << ".R.U.I..IDES..." << std::endl ;
  ss << "SAME.VU.TEX...." << std::endl ;
  ss << "I.E...DUS.I...." << std::endl ;
  ss << "CILS...N..EPURE" << std::endl ;
  ss << ".N.EMBOIREZ...U" << std::endl ;
  ss << ".H.R..MEUH....T" << std::endl ;
  ss << ".A.O..........." << std::endl ;
  ss << ".L.N..........." << std::endl ;
  ss << "WATT..........." << std::endl ;
  ss << "ET............." << std::endl ;
  ss << "B.............." << std::endl ;


  ss << ".......B.EFFARA" << std::endl ;
  ss << ".L..VAGIS..E.AU" << std::endl ;
  ss << "OYE..N.P.G.D.IN" << std::endl ;
  ss << ".C.Q.N.ALOSE.TE" << std::endl ;
  ss << ".R.U.I..IDES..." << std::endl ;
  ss << "SAME.VU.TEX..J." << std::endl ;
  ss << "I.E...DUS.I.RA." << std::endl ;
  ss << "CILS...N..EPURE" << std::endl ;
  ss << ".N.EMBOIREZ...U" << std::endl ;
  ss << ".H.R..MEUH....T" << std::endl ;
  ss << ".A.O..........." << std::endl ;
  ss << ".L.N..........." << std::endl ;
  ss << "WATT..........." << std::endl ;
  ss << "ET............." << std::endl ;
  ss << "B.............." << std::endl ;



  bo->load(ss2);
  std::cout << *bo << std::endl;*/



  std::stringstream ss ;

  ss << "..H..HELA......" << std::endl ;
  ss << ".BOULETE.T....." << std::endl ;
  ss << "..A....SCIAGE.." << std::endl ;
  ss << "TEXANE...R....." << std::endl ;
  ss << "R......QUELS..." << std::endl ;
  ss << "A........F....." << std::endl ;
  ss << "Q........O....." << std::endl ;
  ss << "U......QING...." << std::endl ;
  ss << "E........DU...." << std::endl ;
  ss << "..........N...." << std::endl ;
  ss << "..........Z...." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;


  g.board->load(ss) ;
  Board b(*(g.board));
  /*g.board->setLetter(5,'R',true);

  std::cout << *g.board << std::endl << std::endl;
  Move m ("ENSOUFREE",51,'D',255,255);
  unsigned short int s = g.score(m);
  std::cout << std::endl << "Score final : " << s << std::endl;*/


  g.attribueLettre("OSPDNYD");
  g.print();
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
