#pragma once

#include <string>

class Node {

public:

  Node * tab[27];
  bool is_final;


public:

  Node();

  Node* addNode(const bool & b);

  void addNode(const std::string & s);


};
