#pragma once

#include <string>
#include <queue>


class Node {

public:

  Node * tab[27];
  bool is_final;


public:

  Node();

  //~Node();

  //void freeMemory();

  char getLetter(const unsigned short int & n) const;

  Node* addNode(const bool & b);

  void addNode(const std::string & s);


  void print_letters(Node* node,
                    std::queue<std::pair<char,Node*>> & fifo,
                    const char & c);

  void print();

};
