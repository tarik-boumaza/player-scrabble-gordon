#include "board.hpp"
#include "bag.hpp"
#include "game.hpp"
#include "gaddag.hpp"
#include "player.hpp"

#include <iostream>
#include <sstream>

#include <list>


int main() {

  //Bag * bag = new Bag ();
  //bag->printPoints();

  Game g;
  g.init();

  /*Board * bo = new Board;

  std::stringstream ss2 ;

  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << ".........A....." << std::endl ;
  ss << ".........C....." << std::endl ;
  ss << "...ROB...C....." << std::endl ;
  ss << "....HUM..O..D.." << std::endl ;
  ss << "...DENUENT..U.." << std::endl ;
  ss << "...I.....E..A.." << std::endl ;
  ss << "...V...I.E..L.." << std::endl ;
  ss << "..MOULIN....I.." << std::endl ;
  ss << "...T...FILMOS.." << std::endl ;
  ss << "...S..VA....E.." << std::endl ;
  ss << "......AN....R.." << std::endl ;
  ss << ".......T...JALE" << std::endl ;


  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ; ///
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;


  ss << ".D.B.......N.F." << std::endl ;
  ss << ".E.R.KOP...OHE." << std::endl ;
  ss << ".FRAYAS....BUT." << std::endl ;
  ss << ".O.V.......LIE." << std::endl ;
  ss << ".N.E.A.....ET.L" << std::endl ;
  ss << ".C.R.W......I.I" << std::endl ;
  ss << "TA.E.A.....JE.M" << std::endl ;
  ss << "RI.ZOLIEN..OM.U" << std::endl ; ///
  ss << "A....E..UNGUE.L" << std::endl ;
  ss << "V..QIS.....T..E" << std::endl ;
  ss << "E..........A..." << std::endl ;
  ss << "L..........I..." << std::endl ;
  ss << "O..........S..." << std::endl ;
  ss << "SCIANTE.EX....." << std::endl ;
  ss << "......HUTINS..." << std::endl ;




  bo->load(ss2);
  std::cout << *bo << std::endl;*/

  //std::cout << *g.board << std::endl << std::endl;

  std::stringstream ss ;

  ss << "B...DOUFE.....W" << std::endl ;
  ss << "O.C.I........AU" << std::endl ;
  ss << "B.I.E..ERRATUM." << std::endl ;
  ss << "SURMULET..HATIF" << std::endl ;
  ss << "..O.XI..A....S." << std::endl ;
  ss << "..N..K..N....H." << std::endl ;
  ss << "..N..E..I....SA" << std::endl ;
  ss << "..EVENTAS.....L" << std::endl ; ///
  ss << "...I.T..E.....E" << std::endl ;
  ss << ".J.N....R....ES" << std::endl ;
  ss << ".U.YOD.AA....VE" << std::endl ;
  ss << ".D.L...R.MAPPEZ" << std::endl ;
  ss << "GOGES..R.....Q." << std::endl ;
  ss << ".S.....O.....U." << std::endl ;
  ss << ".......I.....E." << std::endl ;




  g.board->load(ss) ;
  Board b(*(g.board));

  g.attribueLettre("EN","");

  //g.board->spots[133].setLetter('A',true);
  //g.board->spots[87].setLetter('I',true);

/*
  g.print();
  g.moveTurn();
  std::cout << std::endl << std::endl << std::endl;
  g.print();*/



  std::cout << *g.board << std::endl << std::endl;
  Move m ("EN",1,'B',255,255);
  unsigned short int s = g.score(m);
  g.makeMove(m);
  std::cout << *g.board << std::endl << std::endl;
  std::cout << std::endl << "Points marqués : " << s << std::endl;



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
