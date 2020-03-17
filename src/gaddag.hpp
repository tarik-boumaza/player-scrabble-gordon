#pragma once

#include <list>
#include <string>
#include <queue>
#include <utility>


class Node;

class Gaddag {

private:
  Node * first;



private:

  std::list<std::string> mirror(const std::string & word) ;

  void print_letters(Node* node,
                    std::queue<std::pair<char,Node*>> & fifo,
                    const char & c);


public:

  Gaddag();

  ~Gaddag();

  char getLetter(const unsigned short int & n) const;

  void addNodePlus(const std::string & s);

  void addDictionnary();

  void print();

  Node* getFirst();



};
