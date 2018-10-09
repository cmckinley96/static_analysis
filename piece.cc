/******************************************************************
// File: piece.cc
//
//  implementation file for Othello game piece. Stores the state of
//  each piece (W, B, E).
//
//  Colin McKinley || Ohio University
//  Today's Date 8/13/18
*******************************************************************/
#include <iostream>   // Provides cin, cout
#include <string>     // Provides string
#include <cstdlib>    //Provides toupper()
#include "piece.h"    // Header file
#include "colors.h"   // Gives us color formatting
using namespace std;

void piece::output() const{
  if (color_field == EMPTY) {
    cout << "   ";
  } else if (color_field == WHTE) {
    cout << B_WHITE << BLACK << " X " << RESET;
  } else {
    cout << B_BLACK << WHITE << " X " << RESET;
  }
}

void piece::flip(){
  if (color_field == WHTE) {
    color_field = BLK;
  } else {
    color_field = WHTE;
  }
}

void piece::set_color(color_state new_color){
  color_field = new_color;
}

void piece::set_empty(){
  color_field = EMPTY;
}
