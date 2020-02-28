#pragma once

#include <string>
#include <queue>
#include <memory>

class Node {

private:

  Node * tab[27];
  bool is_final;


public:

  Node();

  ~Node();

  char getLetter(const unsigned short int & n) const;

  Node* addNode(const bool & b);

  void addNode(const std::string & s);

  std::vector<std::string> mirror(const std::string & word);

  void addNodePlus(const std::string & s);

  void addDictionnary(const std::string & filename);

  void print_letters(Node* node,
                    std::queue<std::pair<char,Node*>> & fifo,
                    const char & c);

  void print();

};
