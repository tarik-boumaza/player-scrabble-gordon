#pragma once

#include <string>
#include <thread>
#include <queue>

class Node {

private:

  Node * tab[27];
  bool is_final;


public:

  Node();

  Node* addNode(const bool & b);

  char getLetter(const unsigned short int & n) const;

  void addNode(const std::string & s);

  void addNodePlus(const std::string & s);

  void print_letters(Node* node,
                    std::queue<std::pair<char,Node*>> & fifo,
                    const char & c);

  void print();

  std::vector<std::string> mirror(const std::string & word);

  void addDictionnary(const std::string & filename);

  const bool exist(const std::string & s) const;

};
