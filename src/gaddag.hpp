#pragma once

#include <list>
#include <string>
#include <queue>
#include <utility>

#include "map.hpp"


class Gaddag {

private:
  Node * first;


public:
  Gaddag();

  ~Gaddag();

  char getLetter(const unsigned short int & n) const;

  Node* addNode(const bool & b);

  void addNode(const std::string & s);

  std::list<std::string> mirror(const std::string & word) ;

  void addNodePlus(const std::string & s);

  void addDictionnary(const std::string & filename);

  void print_letters(Node* node,
                    std::queue<std::pair<char,Node*>> & fifo,
                    const char & c);

  void print();





};
