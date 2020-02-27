#pragma once


class Player {

private:
  char hand[7];

public:

  Player();

  Player(const char h[7]);

  char getLetter(const unsigned short int & _n) const;

  void setLetter(const unsigned short int & n, const char & c);

  void printHand() const;

};
