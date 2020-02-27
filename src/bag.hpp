#pragma once

#include <string>
#include <mutex>

class Bag {

private:

  std::mutex m;
  unsigned int points[26];
  unsigned int letters[26];
  unsigned int nb_letters;



public:

  Bag();

  Bag(const unsigned int * p[26], const unsigned int * l[26]);

  Bag(const std::string & file_l, const std::string & file_p);

  unsigned short int getPoints(const unsigned short int & c) const;

  char randomDraw();

  Bag& operator=(const Bag & _bag);

  void printLetters() const;

  void printPoints() const;



};
