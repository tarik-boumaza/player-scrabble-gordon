#pragma once

#include <string>

class Node {

private:
  Node * tab[27];
  bool is_final;


private:
  
  Node* addNode(const bool & b);


public:

  Node();

  Node* getNode(const unsigned short int & i) const;

  bool isFinal() const;

  void addNode(const std::string & s);


};
