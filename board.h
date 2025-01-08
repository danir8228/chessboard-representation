//
// Created by Daniela Ramos on 5/2/23.
//

#ifndef CHESSBOARD_BOARD_H
#define CHESSBOARD_BOARD_H

int player; //will only ever be 1 or 2
char board [8][8];

void print_board();
void read_move();
void check_legal(char p, int at_r, int at_c, int to_r, int to_c);

#endif //CHESSBOARD_BOARD_H

/*^ change input
 * ^ use in variables to identify piece and where it is
 * ^ if piece is not in that spot, error and retry
 * - pass in variables and to variables to piece specific function that checks if move is legal
 *      - check if piece can actually move in that manner
 *      - check if piece can circumstancially move to that spot
 * - in that spot, put a dot
 * - in new spot, put that piece
 * */
