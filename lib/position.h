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

#endif //SAKK_POSITION_H

