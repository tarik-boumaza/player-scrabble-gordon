#include "sac.hpp"


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

  nb_letters = 107;

}


Bag::Bag(const unsigned int * p[26], const unsigned int * l[26]) {
  unsigned short int nb = 0;
  for (unsigned int i = 0; i < 26; i++) {
    points[i] = *p[i];
    letters[i] = *l[i];
    nb += points[i];
  }
  nb_letters = nb;
}


Bag::Bag(const std::string & filename) {
  ////////////// HANA /////////////////
}


unsigned short int Bag::getPoints(const unsigned short int & c) const {
  return points[c];
}


char Bag::randomDraw() {
  m.lock();
  char i = 'A';
  int temp = rand()%(nb_letters + 1);
  char last = temp;
  while (temp > 0 && i < 'Z') {
    temp -= letters[static_cast<unsigned short int>(i)];
    if (temp != 0)
      last = temp;
    i++;
  }
  if (i == 'Z') {
    if (temp == 0)
      return 'Z';
    else
      return last;
  }
  else
    return letters[static_cast<unsigned short int>(i)];
  letters[static_cast<unsigned short int>(i)]--;
  nb_letters--;
  return i;
  m.unlock();
}



Bag& Bag::operator=(const Bag & _bag) {
  nb_letters = _bag.nb_letters;
  for (unsigned int i = 0; i < 26; i++) {
    points[i] = _bag.points[i];
    letters[i] = _bag.letters[i];
  }
  return *this;
}
