#include <cstdlib>
#include <iostream>
#include <ctime>
#include "player.hpp"


Player:: Player(const unsigned short int & c) {
  this->id = c;
  for (unsigned int i = 0; i < 7; i++) {
    this->hand[i] = '_';
  }
}


Player:: Player(const unsigned short int & _id, const char h[7]) {
  this->id = _id;
  for(unsigned int i = 0; i < 7; i++) {
    this->hand[i] = h[i];
  }
}


unsigned short int Player::getId() const {
  return this->id;
}


void Player::setId(const unsigned short int & _id) {
  this->id = _id;
}


char Player::getLetter(const unsigned short int & _n) const {
  if (_n < 7)
    return hand[_n];
  return '/';
}


void Player::setLetter(const unsigned short int & n, const char & c) {
  hand[n] = c;
}
