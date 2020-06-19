//
// Created by gigi on 6/17/20.
//

#include "piece.h"
#include "board.h"
#include "position.h"

// 50-50
// function by Gigi
// original Round_Count is even idea by Kuba
COLOR get_current_turn_color() {
    return (Round_Count % 2 == 0) ? WHITE : BLACK;
}

/*
 * Returns true if in a given round, Board[row][col]
 * is the current players own piece.
 * Returns false otherwise.
 */
// kuba and Gigi
bool check_if_own_piece(int row, int col) {
    // WHITE
    COLOR color = get_current_turn_color();
    if (color == WHITE) {
        switch (Board[row][col]) {
            case WHITEPAWN:
            case WHITEKNIGHT:
            case WHITEBISHOP:
            case WHITEROOK:
            case WHITEQUEEN:
            case WHITEKING:
                return 1;
            default:
                return 0;
        }
    }
        // BLACK
    else {
        switch (Board[row][col]) {
            case BLACKPAWN:
            case BLACKKNIGHT:
            case BLACKBISHOP:
            case BLACKROOK:
            case BLACKQUEEN:
            case BLACKKING:
                return 1;
            default:
                return 0;
        }
    }
}

