/*
  Ethan Malenchek   Project 6     April 23, 2018

  This is the main file for the Mancala game Project

*/

#include <iostream>
#include "mancala.h"
using namespace std;

int main(){
     Mancala stonegame;
     game::who winner;
     winner = stonegame.play();

     if(winner == game::HUMAN) {
       cout << "You win!" << endl;
     } else if(winner == game::COMPUTER) {
       cout << "You lose..." << endl;
     }
return 0;
}
