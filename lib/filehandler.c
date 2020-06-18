//
// Created by gigi on 6/17/20.
//

#include <stdio.h>
#include "filehandler.h"

void load_from_file(char* file_name, int step, PIECE_T game_board[BOARD_ROW_SIZE][BOARD_COL_SIZE]) {
    FILE* file_pointer;
    file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL)
        return;
    fscanf(file_pointer, "%d ", &step);
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            fscanf(file_pointer, "%x ", &game_board[i][j]);
        }
    }
    fclose(file_pointer);
}

void save_to_file(char* file_name, int step, PIECE_T game_board[BOARD_ROW_SIZE][BOARD_COL_SIZE]) {
    FILE* file_pointer;
    file_pointer = fopen(file_name, "w");
    if (file_pointer == NULL)
        return;
    fprintf(file_pointer, "%d\n", step);
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            fprintf(file_pointer, "%x ", game_board[i][j]);
        }
        fprintf(file_pointer, "\n");
    }
    fclose(file_pointer);
}