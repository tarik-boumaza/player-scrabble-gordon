#pragma once


class Player {

private:
  char id;
  char hand[7];

public:

  Player(const char & _id);

  Player(const char & _id, const char h[7]);

  char getId() const;

  void setId(const char & _id);

  char getLetter(const char & _n) const;

  void setLetter(const unsigned short int & n, const char & c);

};
