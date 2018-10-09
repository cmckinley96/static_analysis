/******************************************************************
// File: piece.h
//
//  header file for Othello game piece. Stores the state of each
//  piece (W, B, E).
//
//  Colin McKinley || Ohio University
//  Today's Date 8/13/18
*******************************************************************/
#include <iostream>   // Provides cin, cout
#include <string>     // Provides string
#include "game.h"

#ifndef PIECE_H
#define PIECE_H

class piece{
  public:
    enum color_state {EMPTY, BLK, WHTE};
    //Constructor
    piece() {color_field = EMPTY;}

    /**************************
    //Access and mutators
    **************************/

    //Applies proper formatting and output
    void output() const;

    //Returns color of a given space
    color_state color() const{return color_field;}

    //Set empty piece to new color
    void set_color(color_state new_color);

    //Set filled piece to empty
    void set_empty();

    //Flips color when flank occurs
    void flip();

  private:
    color_state color_field;
};

#endif
