//
// Created by gigi on 6/17/20.
//

#include <stdio.h>
#include "file_handler.h"
#include "board.h"
#include "string.h"

/*********** FILE HANDLING ******************/
// kuba
bool load_from_file(char *input_name, int *global_round_count,
                    char *global_p1_name, char *global_p2_name, PIECE_T game_board[BOARD_ROW_SIZE][BOARD_COL_SIZE]) {
    FILE *file_pointer;

    char file_name[100] = "";
    strcpy(file_name, "Saved_Games/");
    strcat(file_name, input_name);

    file_pointer = fopen(file_name, "r");
    if (file_pointer == NULL)
        return false;

    fscanf(file_pointer, "%d ", global_round_count);
    fscanf(file_pointer, "%s ", global_p1_name);
    fscanf(file_pointer, "%s ", global_p2_name);
    for (int i = 0; i < BOARD_COL_SIZE; i++) {
        for (int j = 0; j < BOARD_ROW_SIZE; j++) {
            fscanf(file_pointer, "%x ", &game_board[i][j]);
        }
    }
    fclose(file_pointer);
    return true;
}

// kuba
void save_to_file(char *file_name, int global_round_count, char *global_p1_name, char *global_p2_name) {
    FILE *file_pointer;
    file_pointer = fopen(file_name, "w");
    if (file_pointer == NULL)
        return;

    fprintf(file_pointer, "%d\n", global_round_count); // 1st line: Round_Count
    fprintf(file_pointer, "%s\n", global_p1_name);     // 2nd line: Player_One_Name
    fprintf(file_pointer, "%s\n", global_p2_name);     // 3rd line: Player_Two_Name

    for (int i = 0; i < BOARD_COL_SIZE; ++i) {                 // Subsequent lines: game board
        for (int j = 0; j < BOARD_ROW_SIZE; ++j) {
            fprintf(file_pointer, "%x ", Board[i][j]);
        }
        fprintf(file_pointer, "\n");
    }
    fclose(file_pointer);
}