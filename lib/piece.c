//
// Created by gigi on 6/17/20.
//

#include "piece.h"
#include "board.h"


COLOR get_current_turn_color() {
    return (Round_Count % 2 == 0) ? WHITE : BLACK;
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

void change_hasmoved_values(Position_Data* from_position) {
    if( get_current_turn_color() == WHITE ) {
        switch (from_position->type) {
            case WHITEKING:
                has_moved_white_king = true;
                break;
            case WHITEROOK:
                // check which rook
                if( from_position->colLetter == 2
                    && from_position->rowNumber == 3 ) {
                    has_moved_white_rook_queenside = true;
                } else {
                    has_moved_white_rook_kingside = true;
                }
                break;
            default:
                break;
        }
    } else {
        switch (from_position->type) {
            case BLACKKING:
                has_moved_white_king = true;
                break;
            case BLACKROOK:
                // check which rook
                if( from_position->colLetter == 2
                    && from_position->rowNumber == 3 ) {
                    has_moved_black_rook_queenside = true;
                } else {
                    has_moved_black_rook_kingside = true;
                }
                break;
            default:
                break;
        }
    }
}