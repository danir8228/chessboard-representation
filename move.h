//
// Created by Daniela Ramos on 5/11/23.
//

#ifndef CHESSBOARD_MOVE_H
#define CHESSBOARD_MOVE_H

#include <stdbool.h>

bool is_legal;
bool in_check;

bool pawn_legal(char p, int in_c, int in_r, int to_r, int to_c);
bool bishop_legal(char p, int at_r, int at_c, int to_r, int to_c);
bool knight_legal(char p, int at_r, int at_c, int to_r, int to_c);
bool rook_legal(char p, int at_r, int at_c, int to_r, int to_c);

#endif //CHESSBOARD_MOVE_H

