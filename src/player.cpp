#include <cstdlib>
#include <iostream>
#include <ctime>
#include "player.hpp"


Player::Player() {
  unsigned int i = 0;
  for (i = 0; i < 7; i++) {
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
  if (n < 7) {
    if (c >= 'A' && c <= 'Z') {   // c est une lettre
      hand[n] = c;
      hand_pointer[c - 'A'].push_front(n);
    }
    else if (c == '*') {     // c est un joker
      hand[n] = '*';
      hand_pointer[26].push_front(n);
    }
    else {
      std::cerr << "Caractère spécial détecté : " << c << std::endl 
                << "Sortie..." << std::endl;
      exit(EXIT_FAILURE);
    }
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
  if (c < 'A' || c > 'Z') {   // c n'est pas une lettre
    if (c == '*' && !hand_pointer[26].empty()) {   // c est un joker et le joueur en compte dans sa main
      hand[hand_pointer[26].front()] = '/';
      hand_pointer[26].pop_front();
    }
    else {     // c n'est pas un joker, ou c est un joker et le joueur n'en a pas dans sa main
      std::cerr << "Lettre non disponible... Suppression avortée" << std::endl;
      exit(EXIT_FAILURE);
    }
  }
  else if (hand_pointer[c - 'A'].empty()) {    //c est une lettre que ne possède pas le joueur
    std::cerr << c << " : Erreur liste, lettre non disponible... Suppression avortée"
              << std::endl;
    exit(EXIT_FAILURE);
  }
  else {   // c est une lettre et le joueur en possède
    hand[hand_pointer[c - 'A'].front()] = '/';
    hand_pointer[c - 'A'].pop_front();
  }

}

/////////// A SUPPRIMER \\\\\\\\\\\\//
void Player::removeLetterIndice(const char & n) {
  if (n < 7) {
    hand[n] = '/';
  }
  else {
    std::cerr << "Problème indice" << std::endl;
    exit(EXIT_FAILURE);
  }
}


void Player::printHand() const {
  for(unsigned short int i = 0; i < 7; i++) {
    std::cout << hand[i] << " " << std::flush;
  }
  std::cout << std::endl;
}
