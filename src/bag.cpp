#include <iostream>
#include <fstream>
#include "bag.hpp"

using namespace std;

Bag:: Bag() {
  letters[0] = 9;
  letters[1] = 2;
  letters[2] = 2;
  letters[3] = 3;
  letters[4] = 15;
  letters[5] = 2;
  letters[6] = 2;
  letters[7] = 2;
  letters[8] = 8;
  letters[9] = 1;
  letters[10] = 1;
  letters[11] = 5;
  letters[12] = 3;
  letters[13] = 6;
  letters[14] = 6;
  letters[15] = 2;
  letters[16] = 3;
  letters[17] = 6;
  letters[18] = 6;
  letters[19] = 6;
  letters[20] = 6;
  letters[21] = 2;
  letters[22] = 1;
  letters[23] = 1;
  letters[24] = 1;
  letters[25] = 1;

  points[0] = 1;
  points[1] = 3;
  points[2] = 3;
  points[3] = 2;
  points[4] = 1;
  points[5] = 4;
  points[6] = 2;
  points[7] = 4;
  points[8] = 1;
  points[9] = 8;
  points[10] = 10;
  points[11] = 1;
  points[12] = 2;
  points[13] = 1;
  points[14] = 1;
  points[15] = 3;
  points[16] = 2;
  points[17] = 1;
  points[18] = 1;
  points[19] = 1;
  points[20] = 1;
  points[21] = 4;
  points[22] = 10;
  points[23] = 10;
  points[24] = 10;
  points[25] = 10;

  nb_letters = 102;

}


Bag::Bag(const unsigned int * p[26], const unsigned int * l[26]) {
  unsigned short int nb_l = 0;
  for (unsigned int i = 0; i < 26; i++) {
    points[i] = *p[i];
    letters[i] = *l[i];
    nb_l += letters[i];
  }
  nb_letters = nb_l;
}


Bag::Bag(const std::string & filename_l, const std::string & filename_p) {
    ifstream file_l (filename_l.c_str());
    if (!file_l.is_open()) {
      std::cerr << "Erreur lors de la lecture du fichier " << filename_l <<
                    "\nVeuillez vérifier le chemin du fichier" << endl;
      exit(EXIT_FAILURE);
    }
    else {
      string word, temp;
      unsigned int i = 0, nb = 0;
      while(!file_l.eof() && i < 26) {
        file_l >> word;
        temp = word;
        this->letters[i] = std::stoi(temp);
        nb += std::stoi(temp);
        i++;
      }
      this->nb_letters = nb;
      file_l.close();

      ifstream file_p (filename_p.c_str());
      if (!file_p.is_open()) {
        std::cerr << "Erreur lors de la lecture du fichier " << filename_p <<
                      "\nVeuillez vérifier le chemin du fichier" << endl;
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


char Bag::randomDraw() {
  char res,i;
  i = 'Z';
  int temp = rand()%nb_letters;
  res = 'Z';
  while(temp >= 0 && i >= 'A') {
    if (letters[static_cast<short int>(i - 'A')] != 0)
      temp -= letters[static_cast<short int>(i - 'A')];
    res = i;
    i--;
  }
  if (letters[static_cast<short int>(res - 'A')] > 0)
    letters[static_cast<short int>(res - 'A')]--;
  nb_letters--;
  return res;

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
  char c;
  for(unsigned int i = 0; i < 26; i++) {
    c = 'A' + i;
    std::cout << 'A' + i << " : " << letters[i] << std::endl;
  }
  std::cout << "Nombre total de lettres " << nb_letters << std::endl;
}


void Bag::printPoints() const {
  char c;
  for(unsigned int i = 0; i < 26; i++) {
    c = 'A' + i;
    std::cout << 'A' + i << " : " << points[i] << std::endl;
  }
}
