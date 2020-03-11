#include <iostream>
#include <fstream>
#include "bag.hpp"



Bag::Bag(const std::string & filename_l, const std::string & filename_p) {
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
          this->letters[nb + j] = l;
        }
        l++;
        nb += std::stoi(temp);
        i++;
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
        while(!file_p.eof() && i < 26) {
          file_p >> word;
          temp = word;
          this->points[i] = std::stoi(temp);
          i++;
        }
        file_p.close();
      }
    }
}


unsigned short int Bag::getPoints(const unsigned short int & c) const {
  return points[c];
}


bool Bag::isEmpty() const {
  return (nb_letters == 0);
}


char Bag::randomDraw() {
  if (isEmpty())
    return '/';
  int random_number = rand() % nb_letters;
  char l = letters[random_number];
  letters[random_number] = letters[nb_letters - 1];
  nb_letters--;
  return l;

}


Bag& Bag::operator=(const Bag & _bag) {
  this->nb_letters = _bag.nb_letters;
  for (unsigned int i = 0; i < 26; i++) {
    this->points[i] = _bag.points[i];
    this->letters[i] = _bag.letters[i];
  }
  return *this;
}


void Bag::printLetters() const {
  for(unsigned int i = 0; i < nb_letters; i++) {
    std::cout << letters[i] << std::endl;
  }
  std::cout << "Nombre total de lettres " << nb_letters << std::endl;
}


void Bag::printPoints() const {
  for(unsigned int i = 0; i < 26; i++) {
    std::cout << 'A' + i << " : " << points[i] << std::endl;
  }
}
