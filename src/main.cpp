#include <iostream>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include "game.hpp"

using namespace std;

int main() {
  double temps;
  clock_t t1,t2;
  t1 = clock();


  Game g;
  g.init();
  g.printDico();


  t2 = clock();
  temps = (t2 - t1) / 1000;
  cout << "temps d'exécution : " << temps << " ms" <<  endl;

  return 0;
}
