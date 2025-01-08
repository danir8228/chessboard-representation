#include <stdio.h>
#include <strings.h>
#include <stdbool.h>
#include "board.h"

int main() {
    //printf("Enter 1 zero ('0') at any time to exit the game.\n");
    for (;;) { //infinite loop for now
        print_board();
        read_move();
    }

    return 0;
}

/*bugs:
 * ^ is_legal doesnt update once after mistake
 * ^ bishops take own pieces
 * ^ bishops can't handle moving down
 * - bf3 to e4 with pe5 and pd5 doesnt work sometimes for no reason
 *  - knight move always returns true after first valid move
 *  - Ke1 to f3 then Ne1 to f3
 *  - check if putting an identical move will come back legal (Pe2 to e2)
 * /




/* i absolutely have to:
^ store unplayed pieces in data structure.
^ print unplayed board
^ take player input
^ update data structure to reflect moves
^ if i know all the positions, print the board
- add all _legal functions
- checkmate function that runs after move legal function
- check if zero input and terminate game
^ use player int to force players to take turns

 potentially:
 - put taken piece on the side */


