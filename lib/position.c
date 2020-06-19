//
// Created by gigi on 6/19/20.
//

#include "position.h"
#include <stdlib.h>


Position_Data* new_position_data(PIECE_T type, int colLetter, int rowNumber) {
    Position_Data* position = malloc(sizeof(Position_Data));

    position->type = type;
    position->rowNumber = rowNumber;
    position->colLetter = colLetter;

    return position;
}