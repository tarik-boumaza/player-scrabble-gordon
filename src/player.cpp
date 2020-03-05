#include <cstdlib>
#include <iostream>
#include <ctime>
#include "player.hpp"


Player:: Player() {
  for (unsigned int i = 0; i < 7; i++) {
    this->hand[i] = '/';
  }
}


Player:: Player(const char h[7]) {
  for(unsigned int i = 0; i < 7; i++) {
    this->hand[i] = h[i];
  }
}


char Player::getLetter(const unsigned short int & _n) const {
  if (_n < 7)
    return hand[_n];
  return '/';
}


void Player::setLetter(const unsigned short int & n, const char & c) {
  hand[n] = c;
}


void Player::printHand() const {
  for(unsigned int i = 0; i < 7; i++) {
    std::cout << hand[i] << std::flush;
  }
}
