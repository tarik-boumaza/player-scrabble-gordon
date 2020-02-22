#include "map.hpp"
#include <iostream>
#include <time.h>
#include <stdio.h>

using namespace std;

int main() {
  Noeud n;
  double temps;
  clock_t t1,t2;
  t1 = clock();
  n.addDictionnary("./data/dico.txt");
  //n.print();
  t2 = clock();
  temps = (t2 - t1) / 1000;
  cout << "temps d'exécution : " << temps << " ms" <<  endl;
}




/*
#include "board.hpp"

#include <iostream>
#include <sstream>

int main() {
  Board b ;

  std::cout << b << std::endl ;

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

  b.load(ss) ;

  std::cout << b << std::endl ;

  return 0 ;
}
*/
