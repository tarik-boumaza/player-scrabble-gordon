#include "bonus.hpp"


unsigned char Bonus::getLetterFactor() const {
  return letter_factor;
}


unsigned char Bonus::getWordFactor() const {
  return word_factor;
}

//apply the letter factor on a letter score
unsigned int Bonus::apply_letter(unsigned int score) const {
  return letter_factor * score ;
}

//apply the word factor on a word score
unsigned int Bonus::apply_word(unsigned int score) const {
  return word_factor * score ;
}


Bonus& Bonus::operator = (const Bonus & b){
  this->letter_factor = b.letter_factor;
  this->word_factor = b.word_factor;
  return *this;
}
