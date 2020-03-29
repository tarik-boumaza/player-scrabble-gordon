#pragma once


class Player {

private:
  char hand[7];
  //unsigned short int hand[26];
  unsigned short int points;

public:

  Player();

  Player(const char h[7]);

  char getLetter(const char & c) const;

  unsigned short int getPoints() const;

  void setLetter(const char & n, const char & c);

  void addPoints(const unsigned short int & s);

  void removeLetter(const char & c);

  void printHand() const;

};
