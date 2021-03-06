//
// Created by gigi on 6/19/20.
//

#ifndef SAKK_POSITION_H
#define SAKK_POSITION_H

#include "piece.h"

// Gigi
enum {
    // A1
    WHITE_QUEENSIDE_ROOK_ROW = 8,
    WHITE_QUEENSIDE_ROOK_COL = 1,
    // A8
    BLACK_QUEENSIDE_ROOK_ROW = 1,
    BLACK_QUEENSIDE_ROOK_COL = 1,
};

// Gigi
///************* Position Data ************/
typedef struct Position_Data {
    PIECE_T type;
    int rowNumber;
    int colLetter;
} Position_Data;

Position_Data* new_position_data(PIECE_T type, int colLetter, int rowNumber);

Position_Data* convert_to_position_data(char* from);        // converts input to position data

int convert_tile_number_to_int(char ch);
int convert_tile_letter_to_int(char ch);

void set_has_moved_values(Position_Data* from_position, bool setTo);

#endif //SAKK_POSITION_H

