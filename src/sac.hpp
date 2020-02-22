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

  Bag(const std::string & filename);

  unsigned short int getPoints(const unsigned short int & c) const;

  char randomDraw();

  Bag& operator=(const Bag & _bag);



};
