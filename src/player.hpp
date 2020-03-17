#pragma once


class Player {

private:
  short unsigned int hand[26];

public:

  Player();

  Player(const short unsigned int h[26]);

  short unsigned int getLetter(const char & c) const;

  void setLetter(const char & c);

  void removeLetter(const char & c);

  void printHand() const;

};
