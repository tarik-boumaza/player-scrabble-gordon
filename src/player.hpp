#pragma once

#include <list>


class Player {

private:
  char hand[7];
  std::list<unsigned short int> hand_pointer[27];
  unsigned short int points;

public:

  Player();

  char getLetter(const unsigned short int & n) const;

  unsigned short int getPoints() const;

  void setLetter(const unsigned short int n, const char & c);

  void addPoints(const unsigned short int & s);

  void removeLetter(const char & c);

  void printHand() const;

};
