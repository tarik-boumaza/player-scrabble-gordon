#include "board.hpp"

#include <iostream>

int main() {
  Board b ;

  std::cout << b << std::endl ;

  b.spots[123].letter = 'A' ;
  b.spots[124].letter = 'B' ;
  b.spots[138].letter = 'C' ;
  b.spots[140].letter = 'D' ;
  b.spots[168].letter = 'E' ;

  std::cout << b << std::endl ;

  return 0 ;
}
