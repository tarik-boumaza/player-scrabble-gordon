#include <iostream>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sstream>
#include "bag.hpp"
#include "game.hpp"
#include "board.hpp"

using namespace std;

int main() {
  double temps;
  clock_t t1,t2;
  t1 = clock();


  Game g;
  g.init();


  std::stringstream ss ;
  ss << ".LPHA.ETIQUE..." << std::endl ;
  ss << "L....E........." << std::endl ;
  ss << "P....T........." << std::endl ;
  ss << "H..O.I...L.N..." << std::endl ;
  ss << "A..U.SEGAIES..." << std::endl ;
  ss << "BETISE........." << std::endl ;
  ss << "E..R...A.E....." << std::endl ;
  ss << "T.NEWTON.SIXT.S" << std::endl ;
  ss << "I......O......." << std::endl ;
  ss << "Q......U......." << std::endl ;
  ss << "U......E......." << std::endl ;
  ss << "E......U......." << std::endl ;
  ss << ".....SCRABBLE.." << std::endl ;
  ss << "..............." << std::endl ;
  ss << "..............." << std::endl ;
  g.board->load(ss) ;

  Move m;
  m.word = "ALPHABETIQUE";
  m.first_square = 0;
  m.direction = 'D';

  unsigned short int s = g.score(m);

  std::cout << *g.board << std::endl;
  std::cout << "J'obtiens le score : " << s << std::endl;



/*

std::stringstream ss ;
ss << ".LPHABETIQUE..." << std::endl ;
ss << "L.............." << std::endl ;
ss << "P.............." << std::endl ;
ss << "H.............." << std::endl ;
ss << "A.............." << std::endl ;
ss << "..TISE........." << std::endl ;
ss << "E.............." << std::endl ;
ss << "T...PROJET....." << std::endl ;
ss << "I......O......." << std::endl ;
ss << "Q......U......." << std::endl ;
ss << "U......E......." << std::endl ;
ss << "E......U......." << std::endl ;
ss << ".....SCRABBLE.." << std::endl ;
ss << "..............." << std::endl ;
ss << "..............." << std::endl ;





  Bag ba("./data/letters.txt","./data/points.txt");
  ba.printPoints();


  Board * b;
  std::stringstream ss2 ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "....PROJET....." << std::endl ;
  ss2 << ".......O......." << std::endl ;
  ss2 << ".......U......." << std::endl ;
  ss2 << ".......E......." << std::endl ;
  ss2 << ".......U......." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;
  ss2 << "..............." << std::endl ;

  g.board->load(ss2);
  std::cout << *g.board << std::endl;
*/





  cout << endl;
  t2 = clock();
  temps = (t2 - t1) / 1000;
  cout << "temps d'exécution : " << temps << " ms" <<  endl;

  return 0;
}
