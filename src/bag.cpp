/**
 * @file bag.cpp
*/


#include <iostream>
#include <fstream>
#include <random>
#include "bag.hpp"



Bag::Bag(const std::string & filename_l, 
          const std::string & filename_p,
          const std::string & filename_w1,
          const std::string & filename_w2) {
  
  std::ifstream file_l (filename_l.c_str());
  if (!file_l.is_open()) {
    std::cerr << "Erreur lors de la lecture du fichier " << filename_l <<
                  "\nVeuillez vérifier le chemin du fichier" << std::endl;
    exit(EXIT_FAILURE);
  }
  else {
    std::string word, temp;
    unsigned int i = 0, nb = 0;
    int j;
    char l = 'A';
    while(!file_l.eof() && i < 26) {
      file_l >> word;
      temp = word;
      for (j = 0; j < std::stoi(temp); j++) {
        this->letters[nb + j] = l + i;
      }
      nb += std::stoi(temp);
      i++;
    }
    if (!file_l.eof()) {
      file_l >> word;
      temp = word;
      for (j = 0; j < std::stoi(temp); j++) {
        this->letters[nb + j] = '*';
      }
      nb += std::stoi(temp);
    }
    this->nb_letters = nb;
    file_l.close();

    std::ifstream file_p (filename_p.c_str());
    if (!file_p.is_open()) {
      std::cerr << "Erreur lors de la lecture du fichier " << filename_p <<
                    "\nVeuillez vérifier le chemin du fichier" << std::endl;
      exit(EXIT_FAILURE);
    }
    else {
      i = 0;
      while(!file_p.eof() && i < 27) {
        file_p >> word;
        temp = word;
        this->points[i] = std::stoi(temp);
        i++;
      }

      file_p.close();
    }
  }

  std::ifstream file_w1 (filename_w1.c_str());
  if (!file_w1.is_open()) {
    std::cerr << "Erreur lors de la lecture du fichier " << filename_w1 <<
                  "\nVeuillez vérifier le chemin du fichier" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream file_w2 (filename_w2.c_str());
  if (!file_w2.is_open()) {
    std::cerr << "Erreur lors de la lecture du fichier " << filename_w2 <<
                  "\nVeuillez vérifier le chemin du fichier" << std::endl;
    exit(EXIT_FAILURE);
  }


  std::string word, temp;
  char l = 'A';

  while (!file_w1.eof() && l <= ('Z' + 1)) {
    file_w1 >> word;
    temp = word;
    weights1[l - 'A'] = std::stof(temp);
    l++;
  }

  file_w1.close();

  while (!file_w2.eof() && l <= ('Z' + 1)) {
    file_w2 >> word;
    temp = word;
    weights2[l - 'A'] = std::stof(temp);
    l++;
  }

  file_w2.close();

}


unsigned short int Bag::getPoints(const unsigned char & c) const {
  if (c >= 'A' && c <= 'Z')
    return points[c - 'A'];
  if (static_cast<int>(c) < 26)
    return points[c];
  if (c == '*')
    return points[26];
  std::cerr << static_cast<int>(c) << "Case non déclarée!" << std::endl;
  exit(EXIT_FAILURE);
}


bool Bag::isEmpty() const {
  return (nb_letters == 0);
}


char Bag::randomDraw() {
  if (isEmpty())
    return '/';
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(1,nb_letters);
  int random_number = dis(gen) - 1;
  char l = letters[random_number];
  letters[random_number] = letters[nb_letters - 1];
  nb_letters--;
  return l;

}


void Bag::printLetters() const {
  for(unsigned short int i = 0; i < nb_letters; i++) {
    std::cout << letters[i] << " , " << std::flush;
  }
  std::cout << std::endl << "Nombre total de lettres "
            << nb_letters << std::endl;
}


void Bag::printPoints() const {
  for(unsigned int i = 0; i < 26; i++) {
    std::cout << static_cast<char>('A' + i) << " : "
              << points[i] << std::endl;
  }
  std::cout << "Joker : " << points[26] << std::endl << std::endl;
}


void Bag::printWeights() const {
  for(unsigned int i = 0; i < 26; i++) {
    std::cout << static_cast<char>('A' + i) << " : "
              << weights1[i] << std::endl;
  }
  std::cout << "Joker : " << weights1[26] 
            << std::endl << std::endl;
}
