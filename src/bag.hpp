#pragma once

#include <string>

class Bag {

private:

  unsigned int points[26];
  char letters[102];
  unsigned int nb_letters;



public:

  Bag(const std::string & file_l, const std::string & file_p);

  unsigned short int getPoints(const unsigned char & c) const;

  unsigned short int getPoints(const unsigned short int & c) const;

  bool isEmpty() const;

  char randomDraw();

  Bag& operator=(const Bag & _bag);

  void printLetters() const;

  void printPoints() const;



};
