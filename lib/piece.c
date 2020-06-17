//
// Created by gigi on 6/17/20.
//

#include "piece.h"
#include "board.h"

#include "libsakk.h"        // is_even

bool has_moved_white_king = false;
bool has_moved_white_rook_long = false;
bool has_moved_white_rook_short = false;
bool has_moved_black_king = false;
bool has_moved_black_rook_long = false;
bool has_moved_black_rook_short = false;

COLOR get_current_turn_color() {
    return is_even(round_count) ? WHITE : BLACK;
}

/*
 * Returns true if in a given round, Board[row][col]
 * is the current players own piece.
 * Returns false otherwise.
 */
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