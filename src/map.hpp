#pragma once

#include <string>
#include <queue>

class Noeud {

public:

  char letter;
  Noeud * tab[27];
  bool is_final;


public:

  Noeud();

  Noeud* addNode1(const char & c, const bool & b);

  void addNode(const std::string & s);

  void addNodePlus(const std::string & s);

  void print_letters(Noeud* node, std::queue<Noeud*> & fifo);

  void print();

  std::vector<std::string> mirror(const std::string & word);

  void addDictionnary(const std::string & filename);

  const bool exist(const std::string & s) const;

};
