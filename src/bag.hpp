#pragma once

#include <string>

class Bag {

private:

  unsigned int points[27];
  char letters[104];
  unsigned int nb_letters;



public:

  Bag(const std::string & file_l, const std::string & file_p);

  unsigned short int getPoints(const unsigned char & c) const;

  unsigned short int getPoints(const unsigned short int & c) const;

  bool isEmpty() const;

  char randomDraw();

  void printLetters() const;

  void printPoints() const;



};
