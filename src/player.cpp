#include <cstdlib>
#include <iostream>
#include <ctime>
#include "player.hpp"


Player:: Player() {
  for (unsigned short int i = 0; i < 7; i++) {
    this->hand[i] = '/';
  }
  points = 0;
}


Player:: Player(const char h[7]) {
  for(unsigned short int i = 0; i < 7; i++) {
    this->hand[i] = h[i];
  }
}


char Player::getLetter(const char & c) const {
  if (c >= 0 && c < 7)
    return hand[c];
  std::cerr << "Case non accessible... Sortie!" << std::endl;
  exit(EXIT_FAILURE);
}


unsigned short int Player::getPoints() const {
  return points;
}


void Player::setLetter(const char & n, const char & c) {
  if (n >= 0 && n < 7)
    hand[n] = c;
  else {
    std::cerr << "Case non accessible... Sortie!!" << std::endl;
    exit(EXIT_FAILURE);
  }
}


void Player::addPoints(const unsigned short int & s) {
  points += s;
}


void Player::removeLetter(const char & c) {
  if (c < 'A' || c > 'Z') {
    std::cerr << "Lettre non disponible... Suppression avortée" << std::endl;
    exit(EXIT_FAILURE);
  }

  unsigned short i = 0; {
    while (i < 7) {
      if (hand[i] == c) {
        hand[i]--;
        return;
      }
    }
  }

}


void Player::printHand() const {
  for(unsigned short int i = 0; i < 7; i++) {
    std::cout << hand[i] << " " << std::flush;
  }
  std::cout << std::endl;
}
