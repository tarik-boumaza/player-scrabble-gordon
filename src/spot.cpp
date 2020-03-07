#include "spot.hpp"


unsigned char Spot::getLetterFactor() const {
  return bonus.getLetterFactor();
}


unsigned char Spot::getWordFactor() const {
  return bonus.getWordFactor();
}


char Spot::getLetter() const {
  return letter;
}


void Spot::setLetter(const char & c) {
  letter = c;
}



//display of the spot contents
std::ostream& operator<<(std::ostream& out, Spot s) {

  //triple word color
  static const char* tw = "\033[1;91m" ;
  //double word color
  static const char* dw = "\033[1;95m" ;
  //triple letter color
  static const char* tl = "\033[1;34m" ;
  //double letter color
  static const char* dl = "\033[1;96m" ;
  //reset color
  static const char* reset = "\033[1;0m" ;

  if(s.getLetter() != 0) {
    //a letter is present, show it
    out << s.getLetter() ;
  } else if(s.getWordFactor() == 3) {
    //triple word
    out << tw << "3" << reset ;
  } else if(s.getWordFactor() == 2) {
    //double word
    out << dw << "2" << reset ;
  } else if(s.getLetterFactor() == 3) {
    //triple letter
    out << tl << "3" << reset ;
  } else if(s.getLetterFactor() == 2) {
    //double letter
    out << dl << "2" << reset ;
  } else {
    //nothing interesting
    out << " " ;
  }
  return out ;
}
