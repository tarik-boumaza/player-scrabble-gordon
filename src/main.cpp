/**
 * @file main.cpp
*/


#include "scrabbleTXT.hpp"
#include <iostream>
#include <cstring>


int main(int argc, char** argv) {

  if (argc > 3) {
    std::cerr << "ERREUR : trop d'arguments" << std::endl;
    exit(EXIT_FAILURE);
  }

  bool sm = false;
  bool ia = false;

  for (int i = 1; i < argc; i++) {
    if (!strcmp(argv[i], "--sm"))
      sm = true;
    else if (!strcmp(argv[i], "--ia"))
      ia = true;
    else {
      std::cerr << "OPTION INCONNUE : " << argv[i] << std::endl;
      exit(EXIT_FAILURE);
    }
  }


  ScrabbleTXT * scrabble = new ScrabbleTXT(sm,ia);
  scrabble->play();
  delete scrabble;

  return 0;
}
