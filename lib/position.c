//
// Created by gigi on 6/19/20.
//

#include "position.h"
#include <stdlib.h>
#include "board.h"      // access to Board array and has_moved bools
#include "ctype.h"      // tolower

// Gigi
Position_Data* new_position_data(PIECE_T type, int colLetter, int rowNumber) {
    Position_Data* position = malloc(sizeof(Position_Data));

    position->type = type;
    position->rowNumber = rowNumber;
    position->colLetter = colLetter;

    return position;
}

// 50-50
Position_Data* convert_to_position_data(char* from) {

    // Kuba
    int from_letter = convert_tile_letter_to_int(from[0]);
    int from_number = convert_tile_number_to_int(from[1]);

    // Gigi
    PIECE_T fromPiece = Board[from_number][from_letter];

    Position_Data* position = new_position_data(fromPiece, from_letter, from_number);

    return position;
}

/*
 * Handles the conversion from Tile letter to int.
 * Returns the proper array selector for the Tile.
 * A -> 1
 * B -> 2
 * C -> 3
 * D -> 4
 * E -> 5
 * F -> 6
 * G -> 7
 * H -> 8
 */
// kuba
int convert_tile_letter_to_int(char ch) {

    return tolower(ch) - 'a' + 1;
}

/*
 * Handles the conversion from Tile number to int.
 * Returns the proper array selector for the Tile.
 * 1 -> 8
 * 2 -> 7
 * 3 -> 6
 * 4 -> 5
 * 5 -> 4
 * 6 -> 3
 * 7 -> 2
 * 8 -> 1
 */
// kuba
int convert_tile_number_to_int(char ch) {

    return 9 - (ch - '0');
}

// Gigi
void set_has_moved_values(Position_Data* from_position, bool setTo) {
    if( get_current_turn_color() == WHITE ) {
        switch (from_position->type) {
            case WHITEKING:
                has_moved_white_king = setTo;
                break;
            case WHITEROOK:
                // check which rook
                if(from_position->colLetter == WHITE_QUEENSIDE_ROOK_COL
                    && from_position->rowNumber == WHITE_QUEENSIDE_ROOK_ROW ) {
                    has_moved_white_rook_queenside = setTo;
                } else {
                    has_moved_white_rook_kingside = setTo;
                }
                break;
            default:
                break;
        }
    } else {
        switch (from_position->type) {
            case BLACKKING:
                has_moved_black_king = setTo;
                break;
            case BLACKROOK:
                // check which rook
                if(from_position->colLetter == BLACK_QUEENSIDE_ROOK_COL
                    && from_position->rowNumber == BLACK_QUEENSIDE_ROOK_ROW ) {
                    has_moved_black_rook_queenside = setTo;
                } else {
                    has_moved_black_rook_kingside = setTo;
                }
                break;
            default:
                break;
        }
    }
}
