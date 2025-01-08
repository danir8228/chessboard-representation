//
// Created by Daniela Ramos on 5/11/23.
//

#include "move.h"
#include "board.h"
#include "stdio.h"
#include <stdbool.h>
#include <ctype.h>

/* external variables */
bool is_legal;
bool in_check;

/*prototypes*/
bool bishop_test(int on_r, int on_c, int to_r, int to_c);


/* pawn_legal:
     * move forward one space (if nothing is there)
     * move forward two spaces (if nothing is there and you started on row index 6)
     * move diagonally one in either direction (if an opponent's piece is there)
     * returns bool indicating if pawn move is legal or not
     * */

bool pawn_legal (char p, int at_r, int at_c, int to_r, int to_c) {

    if (player == 1) {
        if (&board[to_r][to_c] == &board[at_r - 1][at_c] && board[to_r][to_c] == '.')
            is_legal = true;
        else if (&board[to_r][to_c] == &board[at_r - 2][at_c] && board[to_r][to_c] == '.' && at_r == 6)
            is_legal = true;
        else if (&board[to_r][to_c] == &board[at_r - 1][at_c - 1] || &board [to_r][to_c] == &board [at_r - 1][at_c + 1] \
        && !isupper(board[to_r][to_c]))
            is_legal = true;
        else
            is_legal = false;
    }
    else if (player == 2) {
        if (&board[to_r][to_c] == &board[at_r + 1][at_c] && board[to_r][to_c] == '.')
            is_legal = true;
        else if (&board[to_r][to_c] == &board[at_r + 2][at_c] && board[to_r][to_c] == '.' && at_r == 1)
            is_legal = true;
        else if (&board[to_r][to_c] == &board[at_r + 1][at_c - 1] || &board [to_r][to_c] == &board [at_r + 1][at_c + 1] \
        && isupper(board[to_r][to_c]))
            is_legal = true;
        else
            is_legal = false;
    }
    else //somehow player is not 1 or 2
        printf("Error with player variable");

    return is_legal;
}

bool bishop_legal(char p, int at_r, int at_c, int to_r, int to_c) {
    int on_r, on_c; //step-through variables

    if (at_r > to_r) { //if destination is above current position
        if (at_c < to_c) { //if destination is on the right of pos
            on_r = at_r - 1; //setting on variables to the next possible move forward
            on_c = at_c + 1;
            while (&board[on_r + 1][on_c - 1] != &board[to_r][to_c]) {
                printf("in while loop "); //debugging
                printf("on:%d ", on_c);
                printf("to:%d\n", to_c);
                if (!bishop_test(on_r, on_c, to_r, to_c)) //if not true, return that immediately
                    return is_legal;
                on_r -= 1;
                on_c += 1;
            }
            is_legal = true; //if completes loop successfully (no self-take) then move is legal
        }
        else if (at_c > to_c) { //destination is on the left of pos
            on_r = at_r - 1;
            on_c = at_c - 1;
            while (&board[on_r + 1][on_c + 1] != &board[to_r][to_c]) {
                printf("in while loop ");
                printf("on:%d ", on_c);
                printf("to:%d\n", to_c);
                if (!bishop_test(on_r, on_c, to_r, to_c))
                    return is_legal;
                on_r -= 1;
                on_c -= 1;
            }
            is_legal = true;
        }
        else // destination in the same column as pos
            is_legal = false;
    }
    else if (at_c < to_r) { // if destination is below current position
        if (at_c < to_c) { //if destination is on the right of pos
            on_r = at_r + 1; //setting on variables to the next possible move forward
            on_c = at_c + 1;
            while (&board[on_r - 1][on_c - 1] != &board[to_r][to_c]) {
                printf("in while loop "); //debugging
                printf("on:%d ", on_c);
                printf("to:%d\n", to_c);
                if (!bishop_test(on_r, on_c, to_r, to_c)) //if not true, return that immediately
                    return is_legal;
                on_r += 1;
                on_c += 1;
            }
            is_legal = true; //if completes loop successfully (no self-take) then move is legal
        }
        else if (at_c > to_c) { //destination is on the left of pos
            on_r = at_r + 1;
            on_c = at_c - 1;
            while (&board[on_r - 1][on_c + 1] != &board[to_r][to_c]) {
                printf("in while loop ");
                printf("on:%d ", on_c);
                printf("to:%d\n", to_c);
                if (!bishop_test(on_r, on_c, to_r, to_c))
                    return is_legal;
                on_r += 1;
                on_c -= 1;
            }
            is_legal = true;
        }
        else // destination in the same column as pos
            is_legal = false;
    }
    else //destination is in the same row as pos
        is_legal = false;

    return is_legal;
}


bool bishop_test(int on_r, int on_c, int to_r, int to_c) {
    is_legal = true; //just in case it's set to false

    if (player == 1) {
        if (isupper(board[on_r][on_c])) { //not legal if taking or going through own piece
            printf("saw upper (own)\n");
            is_legal = false;
        }
        if (on_c == to_c && on_r != to_r) { //not legal if not on the diagonal
            printf("in same column but not right spot\n");
            is_legal = false;
        }
        if (islower(board[on_r][on_c]) && &board[on_r][on_c] != &board[to_r][to_c]) { //not legal is phasing through piece
            printf("phasing through opponent's piece\n");
            is_legal = false;
        }
    }
    else if (player == 2) {
        if (islower(board[on_r][on_c])) { //not legal if taking or going through own piece
            printf("saw lower (own)\n");
            is_legal = false;
        }
        if (on_c == to_c && on_r != to_r) { //not legal if not on the diagonal
            printf("in same column but not right spot\n");
            is_legal = false;
        }
        if (isupper(board[on_r][on_c]) && &board[on_r][on_c] != &board[to_r][to_c]) { //not legal is phasing through piece
            printf("phasing through opponent's piece\n");
            is_legal = false;
        }
    }
    else //somehow player is not 1 or 2
        printf("Error with player variable");


    return is_legal;
}

bool knight_legal(char p, int at_r, int at_c, int to_r, int to_c) {
    int on_r, on_c; //potential move placeholders
    int i;

    typedef struct {
        int r;
        int c;
    } Move;

    Move poss_moves[8];

    //0
    on_r = at_r - 2;
    on_c = at_c + 1;
    poss_moves[0].r = on_r;
    poss_moves[0].c = on_c;

    //1
    on_r = at_r - 1;
    on_c = at_c + 2;
    poss_moves[1].r = on_r;
    poss_moves[1].c = on_c;

    //2
    on_r = at_r + 1;
    on_c = at_c + 2;
    poss_moves[2].r = on_r;
    poss_moves[2].c = on_c;

    //3
    on_r = at_r + 2;
    on_c = at_c + 1;
    poss_moves[3].r = on_r;
    poss_moves[3].c = on_c;

    //4
    on_r = at_r + 2;
    on_c = at_c - 1;
    poss_moves[4].r = on_r;
    poss_moves[4].c = on_c;

    //5
    on_r = at_r + 1;
    on_c = at_c - 2;
    poss_moves[5].r = on_r;
    poss_moves[5].c = on_c;

    //6
    on_r = at_r - 1;
    on_c = at_c - 2;
    poss_moves[6].r = on_r;
    poss_moves[6].c = on_c;

    //7
    on_r = at_r - 2;
    on_c = at_c - 1;
    poss_moves[7].r = on_r;
    poss_moves[7].c = on_c;

    /*for (i = 0; i < 8; i++)
        printf("(%d,%d)", poss_moves[i].r, poss_moves[i].c); */


    for (i = 0; i < 8; i ++) {
        if (to_r == poss_moves[i].r && to_c == poss_moves[i].c) { //legal if move is in set of poss_moves
            if (poss_moves[i].r > 7 || poss_moves[i].r < 0 || poss_moves[i].c > 7 || poss_moves[i].c < 0) {
                is_legal = false;
            }
            else if (player == 1 && isupper(board[poss_moves[i].r][poss_moves[i].c])) //not legal if taking own piece
                is_legal = false;
            else if (player == 2 && islower(board[poss_moves[i].r][poss_moves[i].c]))
                is_legal = false;
            else
                is_legal = true;
        }
    }

    return is_legal;
}

bool rook_test() {

}

bool rook_legal(char p, int at_r, int at_c, int to_r, int to_c) {
  int on_r, on_c;

    if (at_r == to_r) { //move on the horizontal
        if (at_c < to_c) { // if destination is on the right of pos
            on_r = at_r + 1; //setting to next poss move
            while (&board[on_r - 1][to_c] != &board[to_r][to_c]) {
                //rook_test();
            }
        }
        else if (at_c > to_c) {

        }
    }
    else if (at_c == to_c) { //move on the vertical

    }
    else
        is_legal = false;

}