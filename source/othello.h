/******************************************************************
// File: othello.h
//
//  Header file for Othello game, which is a child of game.
//  Contains specifics for conducting a game of Othello.
//
//  Colin McKinley || Ohio University
//  Today's Date 8/13/18
*******************************************************************/
#include <iostream>   //Provide cin, cout
#include <string>     //String class
#include <queue>      //STL queue
#include "game.h"     //Provide parent class
#include "piece.h"    //Provide piece class for game board

#ifndef OTHELLO_H
#define OTHELLO_H

class Othello : public main_savitch_14::game{
  public:
    //Constructor, might not need
    //Othello();

    /*********************************
    /   Virtual Functions            /
    *********************************/
    void make_move(const std::string& move);
    void restart();
    void display_status() const;
    bool is_legal(const std::string& move) const;
    bool is_game_over() const;
    std::string get_user_move() const;
    main_savitch_14::game::who winning() const;
    int evaluate() const;
    game* clone() const{return new Othello(*this);}
    void compute_moves(std::queue<std::string>& moves) const;

    /********************************
    /   Helper functions            /
    ********************************/
    //Check whether a player has any moves left
    bool can_player_pass(game::who player) const;
    //Decides whether a given move is valid for the other player
    bool is_legal_previous(const std::string& move) const;

    /********************************
    /   Functions for searching     /
    ********************************/
    bool look_left(int row, int col, piece::color_state target) const;
    bool look_up_left(int row, int col, piece::color_state target) const;
    bool look_up(int row, int col, piece::color_state target) const;
    bool look_up_right(int row, int col, piece::color_state target) const;
    bool look_right(int row, int col, piece::color_state target) const;
    bool look_down_right(int row, int col, piece::color_state target) const;
    bool look_down(int row, int col, piece::color_state target) const;
    bool look_down_left(int row, int col, piece::color_state target) const;

    /********************************
    /   Functions for state change  /
    ********************************/
    void change_left(int row, int col, piece::color_state target);
    void change_up_left(int row, int col, piece::color_state target);
    void change_up(int row, int col, piece::color_state target);
    void change_up_right(int row, int col, piece::color_state target);
    void change_right(int row, int col, piece::color_state target);
    void change_down_right(int row, int col, piece::color_state target);
    void change_down(int row, int col, piece::color_state target);
    void change_down_left(int row, int col, piece::color_state target);

  private:
    static const int DIMENSION = 8;
    piece board[DIMENSION][DIMENSION];
};



#endif
