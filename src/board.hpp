#pragma once

#include "spot.hpp"

#include <iostream>

/* Scrabble board */

class Board {
  //default initialization of a scrabble board

public:

  Board() ;

  //i/o to files
  void save(std::ostream& out) ;
  void load(std::istream& in) ;

  //access to the spots by coordinates
  Spot operator()(unsigned char l, unsigned char c) const ;
  Spot& operator()(unsigned char l, unsigned char c) ;

  unsigned char getWordFactor(const unsigned int & id) const;

  unsigned char getLetterFactor(const unsigned int & id) const;


private:
  Spot spots[225] ;
  
} ;

//board display on the console
std::ostream& operator<<(std::ostream& out, const Board& b) ;
