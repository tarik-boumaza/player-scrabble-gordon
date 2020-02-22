#include <cstdlib>
#include <iostream>
#include <ctime>
#include "player.hpp"


Player:: Player(const char & c) {
  this->id = c;
  for (unsigned int i = 0; i < 7; i++) {
    this->hand[i] = '_';
  }
}


Player:: Player(const char & c, const char h[7]) {
  this->id = c;
  for(unsigned int i = 0; i < 7; i++) {
    this->hand[i] = h[i];
  }
}


char Player::getId() const {
  return this->id;
}


void Player::setId(const char & _id) {
  this->id = _id;
}


char Player::getLetter(const char & _n) const {
  if (_n >= 0 && _n < 6)
    return hand[static_cast<unsigned int>(_n)];
  return '/';
}


void Player::setLetter(const unsigned short int & n, const char & c) {
  hand[n] = c;
}
