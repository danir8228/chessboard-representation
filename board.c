//
// Created by Daniela Ramos on 5/2/23.
//

#include "board.h"
#include <stdio.h>
#include <ctype.h>
#include "move.h"

#define R 8
#define C 8

#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_RESET   "\x1b[0m"

/* external variables */
bool first_time = true;
int player; //will only ever be 1 or 2
char board [8][8] = {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r',
                     'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p',
                     '.', '.', '.', '.', '.', '.', '.', '.',
                     '.', '.', '.', '.', '.', '.', '.', '.',
                     '.', '.', '.', '.', '.', '.', '.', '.',
                     '.', '.', '.', '.', '.', '.', '.', '.',
                     'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P',
                     'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'};


/* function prototypes */
//it said they were redundant?


void print_board(void) {
    int i, j, object;

    for (i = 0; i < R; i ++) {
        printf("\n");
        for (j = 0; j < C; j ++) {
            object = board [i] [j];
            printf(" %c ", object);
        }
        printf(ANSI_COLOR_YELLOW " %d" ANSI_COLOR_RESET, 8 - i);
    }
    printf("\n");
    printf(ANSI_COLOR_YELLOW " a  b  c  d  e  f  g  h" ANSI_COLOR_RESET);
    printf("\n\n");
}

/*input_ask():
        * asks user for move input
        * scans and converts input into index variables */

void input_ask(int *in_at_r, int *in_to_r, char *p, char *in_at_c, char *in_to_c,int *at_r, int *at_c, int *to_c, int *to_r) {
    int converter [8] = {7, 6, 5, 4, 3, 2, 1, 0}, c;

    if (!first_time)
        while ((c = getchar()) != '\n' && c != EOF) {} //clearing the buffer

    printf("Enter move in 'Pe3 to d4' format (starting square and piece, then its destination): ");
    scanf("%c%c%d to %c%d", p, in_at_c, in_at_r, in_to_c, in_to_r);

    /*if (p == '0') {
        exit(EXIT_SUCCESS);
    } todo add condition so it terminates if input is 0*/

    //turning input into index
    *at_c = *in_at_c - 'a';
    *at_r = converter [*in_at_r - 1];

    *to_c = *in_to_c - 'a';
    *to_r = converter [*in_to_r - 1];
}

/*read_move():
        * coordinates calls of input_ask() to get functional input
        * coordinates calls of check_legal() to get legal input
        * edits board to reflect legal move */

void read_move(void) {
    int in_at_r, at_r, at_c, in_to_r, to_r, to_c, c;
    char p, in_at_c, in_to_c;

    //setting player variable
    if (!first_time) {
        if (player == 1) player = 2;
        else player = 1;
    }
    else
        player = 1;

    //printf("Enter 1 zero ('0') at any time to exit the game.\n");
    input_ask(&in_at_r, &in_to_r, &p, &in_at_c, &in_to_c, &at_r, &at_c, &to_c, &to_r);

    first_time = false;

    while (board[at_r][at_c] != p) { //loop forces user to input piece and position that exist
        printf("Your inputted piece, %c, is not at %c%d. Please try again. \n\n", p, in_at_c, in_at_r);
        //printf("%c%c%d (%d %d) to %c%d (%d %d) \n", p, in_at_c, in_at_r, at_c, at_r, in_to_c, in_to_r, to_c, to_r);
        input_ask(&in_at_r, &in_to_r, &p, &in_at_c, &in_to_c, &at_r, &at_c, &to_c, &to_r);
    }

    while (player == 1 && islower(p)) { //loop forces player 1 to move uppercase pieces
        printf("Player 1 must move the uppercase pieces. Please try again. \n\n");
        input_ask(&in_at_r, &in_to_r, &p, &in_at_c, &in_to_c, &at_r, &at_c, &to_c, &to_r);
    }

    while (player == 2 && isupper(p)) { //loop forces player 2 to move lowercase pieces
        printf("Player 2 must move the lowercase pieces. Please try again. \n\n");
        input_ask(&in_at_r, &in_to_r, &p, &in_at_c, &in_to_c, &at_r, &at_c, &to_c, &to_r);
    }


    printf("%c%c%d (%d %d) to %c%d (%d %d) \n", p, in_at_c, in_at_r, at_c, at_r, in_to_c, in_to_r, to_c, to_r);


    do {
        check_legal(p, at_r, at_c, to_r, to_c);

        if (is_legal) {
            board[at_r][at_c] = '.';
            board[to_r][to_c] = p;
        }
        else {
            printf("%c%c%d to %c%d is not a legal move. Please try again.\n", p, in_at_c, in_at_r, in_to_c, in_to_r);
            input_ask(&in_at_r, &in_to_r, &p, &in_at_c, &in_to_c, &at_r, &at_c, &to_c, &to_r);
        }

    } while (!is_legal);
}


/*check_legal():
        * calls other _legal funcs
        * checks if move is legal by piece */

void check_legal(char p, int at_r, int at_c, int to_r, int to_c) {

    switch (p) {
        /*case 'K':
        case 'k':
            king_legal(p, at_r, at_c, to_r, to_c);
            break;
        case 'Q':
        case 'q':
            queen_legal(p, at_r, at_c, to_r, to_c);
            break; */
        case 'R':
        case 'r':
            rook_legal(p, at_r, at_c, to_r, to_c);
            break;
        case 'N':
        case 'n':
            printf("%d",knight_legal(p, at_r, at_c, to_r, to_c));
            break;
        case 'B':
        case 'b':
            printf("%d", bishop_legal(p, at_r, at_c, to_r, to_c));
            break;
        case 'P':
        case 'p':
            printf("%d", pawn_legal(p, at_r, at_c, to_r, to_c));
            break;
        default:
            printf("Error: invalid piece.");
            break;
    }
}