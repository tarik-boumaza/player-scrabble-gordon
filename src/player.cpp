#include <cstdlib>
#include <iostream>
#include <ctime>
#include "player.hpp"


Player:: Player() {
  for (unsigned short int i = 0; i < 26; i++) {
    this->hand[i] = 0;
  }
}


Player:: Player(const short unsigned int h[26]) {
  for(unsigned short int i = 0; i < 26; i++) {
    this->hand[i] = h[i];
  }
}


unsigned short int Player::getLetter(const char & c) const {
  if (c < 26)
    return hand[c];
  if (c >= 'A' && c <= 'Z')
    return hand[c - 'A'];
  std::cerr << "Case non accessible... Sortie" << std::endl;
  exit(EXIT_FAILURE);
}


void Player::setLetter(const char & c) {
  if (c < 26)
    hand[c]++;
  else
    hand[c - 'A']++;
}


void Player::removeLetter(const char & c) {
  if (c < 26)
    if (hand[c] > 0)
      hand[c]--;
    else {
      std::cerr << "Lettre non disponible... Suppression avortée" << std::endl;
      exit(EXIT_FAILURE);
    }
  else
    if (hand[c - 'A'] > 0)
      hand[c - 'A']--;
    else {
      std::cerr << "Lettre non disponible... Suppression avortée" << std::endl;
      exit(EXIT_FAILURE);
    }
}


void Player::printHand() const {
  for(unsigned short int i = 0; i < 26; i++) {
    std::cout << hand[i] << " " << std::flush;
  }
  std::cout << std::endl;
}
