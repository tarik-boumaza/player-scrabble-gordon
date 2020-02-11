#pragma once

#include "spot.hpp"

#include <iostream>

/* Scrabble board */

struct Board {
  //default initialization of a scrabble board
  Board() ;

  //access to the spots by coordinates
  Spot operator()(unsigned char l, unsigned char c) const ;
  Spot& operator()(unsigned char l, unsigned char c) ;

  //spots are public, and can therefore also be accessed b index
  Spot spots[225] ;
} ;

//board display on the console
std::ostream& operator<<(std::ostream& out, const Board& b) ;
