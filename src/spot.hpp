#pragma once

#include "bonus.hpp"

#include <iostream>


class Spot {


private:
  char letter;
  Bonus bonus;


public:
  Spot() :
    letter(0)
  {}

  Spot(unsigned char lf, unsigned char wf) :
    letter(0), bonus(lf, wf)
  {}


  unsigned char getLetterFactor() const;

  unsigned char getWordFactor() const;

  char getLetter() const;

  void setLetter(const char & c);

} ;

//display of the spot contents
std::ostream& operator<<(std::ostream& out, Spot s) ;
