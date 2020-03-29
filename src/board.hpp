#pragma once

#include "spot.hpp"

#include <iostream>
#include <list>

struct Move{
  std::string word;
  unsigned char first_square;
  char direction;

  Move(){};

  Move(const std::string w, const unsigned char & fq, const char & d) {
    word = w;
    first_square = fq;
    direction = d;
  }

  Move& operator = (const Move& m){
    word = m.word;
    first_square = m.first_square;
    direction = m.direction;
  }

};

/* Scrabble board */

class Board {
  //default initialization of a scrabble board
public:
  std::list<unsigned char> getAnchorSquares();
  std::pair<unsigned char,unsigned char> getIndice(const unsigned char& n);
  unsigned short int getIndice(const unsigned char & x,const unsigned char &y);
  Spot* getSpot(const unsigned char & i) ;

public:

  Board() ;
  Board(const Board& copy);
  //i/o to files
  void save(std::ostream& out) ;
  void load(std::istream& in) ;

  //access to the spots by coordinates
  Spot operator()(unsigned char l, unsigned char c) const ;
  Spot& operator()(unsigned char l, unsigned char c) ;


  char getLetter(const unsigned char & i) const;

  void setLetter(const unsigned char & n, const char & c);

  unsigned short int getWordFactor(const unsigned char & id) const;

  unsigned short int getLetterFactor(const unsigned char & id) const;

  Board& operator = (const Board& b);



private:
  Spot spots[225] ;

} ;

//board display on the console
std::ostream& operator<<(std::ostream& out, const Board& b) ;
