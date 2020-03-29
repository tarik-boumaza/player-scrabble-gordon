#include "scrabbleTXT.hpp"

int main() {

  ScrabbleTXT * scrabble = new ScrabbleTXT;
  scrabble->play();
  delete scrabble;

  return 0;
}
