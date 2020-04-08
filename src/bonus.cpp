#include "bonus.hpp"


unsigned char Bonus::getLetterFactor() const {
  return letter_factor;
}


unsigned char Bonus::getWordFactor() const {
  return word_factor;
}


Bonus& Bonus::operator = (const Bonus & b){
  this->letter_factor = b.letter_factor;
  this->word_factor = b.word_factor;
  return *this;
}
