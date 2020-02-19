#pragma once

#include <string>
#include <unordered_map>

class Noeud {

private:
  std::unordered_map<char, Noeud*> node;
  bool is_final;


public:

  Noeud();

  void addNode(const char & c, const bool & b);

  void addNode(const std::string & s);

  void print() const;

  void print_hashmap(const std::unordered_map<char,Noeud*> & m) const;

};
