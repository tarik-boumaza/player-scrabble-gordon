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

char Player::getLetter(const unsigned short int & n) const {
  if (n < 7)
    return hand[n];
  std::cerr << "Case non accessible... Sortie!" << std::endl;
  exit(EXIT_FAILURE);
}


unsigned short int Player::getPoints() const {
  return points;
}


void Player::setLetter(const unsigned short int n, const char & c) {
  if (n < 7 && c >= 'A' && c <= 'Z') {
    hand[n] = c;
    hand_pointer[c - 'A'].push_front(n);
  }
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
  if (hand_pointer[c - 'A'].empty() ){
    std::cerr << c << " : Erreur liste, lettre non disponible... Suppression avortée"
              << std::endl;
    //printHand();
    exit(EXIT_FAILURE);
  }

  hand[hand_pointer[c - 'A'].back()] = '/';
  hand_pointer[c - 'A'].pop_back();
}


void Player::printHand() const {
  for(unsigned short int i = 0; i < 7; i++) {
    std::cout << hand[i] << " " << std::flush;
  }
  std::cout << std::endl;
}
