/**
 * @file main.cpp
*/


#include "scrabbleTXT.hpp"
#include <iostream>
#include <cstring>


int main(int argc, char** argv) {

  if (argc > 2) {
    std::cerr << "ERREUR : trop d'arguments" << std::endl;
     exit(EXIT_FAILURE);
  }
  
  if (argc == 1) {
    ScrabbleTXT * scrabble = new ScrabbleTXT;
    scrabble->play(false);
    delete scrabble;
  }
  else {
    bool b (!strcmp(argv[1], "--sm"));
    if (b) {
      ScrabbleTXT * scrabble = new ScrabbleTXT;
      scrabble->play(true);
      delete scrabble;
    }
    else {
      std::cerr << "OPTION INCONNUE : " << argv[1] << std::endl;
      exit(EXIT_FAILURE);
    }
  } 

  return 0;
}
