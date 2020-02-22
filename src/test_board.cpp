#include "map.hpp"
#include <iostream>

int main() {
  Noeud * n = new Noeud();
  n->addNode("etudiant");
  n->addNode("etudiante");
  n->addNode("etrangere");
  n->addNode("scrabble");
  n->addNode("bonsoir");
  n->addNode("scrabb");
  n->print();
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
