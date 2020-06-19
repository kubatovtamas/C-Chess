//
// Created by gigi on 6/19/20.
//

#ifndef SAKK_POSITION_H
#define SAKK_POSITION_H

#include "piece.h"

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

#endif //SAKK_POSITION_H
