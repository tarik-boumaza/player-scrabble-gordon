#pragma once

#include <string>
#include <thread>
#include <queue>

class Node {

private:

  char letter;
  Node * tab[27];
  bool is_final;


public:

  Node();

  Node* addNode1(const char & c, const bool & b);

  void addNode(const std::string & s);

  void addNodePlus(const std::string & s);

  void print_letters(Node* node, std::queue<Node*> & fifo);

  void print();

  std::vector<std::string> mirror(const std::string & word);

  void addDictionnary(const std::string & filename);

  const bool exist(const std::string & s) const;

};
