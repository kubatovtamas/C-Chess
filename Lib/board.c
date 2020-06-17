//
// Created by gigi on 6/14/20.
//

#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>         // memcpy

#include "board.h"
#include "piece.h"



//_Bool is_even(round_count) ? white : black
bool has_moved_white_king = false;
bool has_moved_white_rook_long = false;
bool has_moved_white_rook_short = false;
bool has_moved_black_king = false;
bool has_moved_black_rook_long = false;
bool has_moved_black_rook_short = false;

// Board tester
// Starting Position
PIECE_T Board[BOARD_ROW_SIZE][BOARD_COL_SIZE] = {
        // Black
        {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'},
        {'8', BLACKROOK, BLACKKNIGHT, BLACKBISHOP, BLACKQUEEN, BLACKKING, BLACKBISHOP, BLACKKNIGHT, BLACKROOK, '8'},
        {'7', BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, '7'},
        {'6', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '6'},
        {'5', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '5'},
        {'4', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '4'},
        {'3', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', '3'},
        {'2', WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, '2'},
        {'1', WHITEROOK, WHITEKNIGHT, WHITEBISHOP, WHITEQUEEN, WHITEKING, WHITEBISHOP, WHITEKNIGHT, WHITEROOK, '1'},
        {' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H'}
        // White
};

/*
 * Resets the board to the starting state.
 * Overwrites the memory of the starting Board,
 * so it may not be okay for long term use
 * (as we don't have functionality for saving Rounds/Steps)
 */
void reset_board() {
    PIECE_T original_board[BOARD_ROW_SIZE][BOARD_COL_SIZE] = {
            // Black
            {' ', 'A',       'B',         'C',         'D',        'E',       'F',         'G',         'H'},
            {'8', BLACKROOK, BLACKKNIGHT, BLACKBISHOP, BLACKQUEEN, BLACKKING, BLACKBISHOP, BLACKKNIGHT, BLACKROOK, '8'},
            {'7', BLACKPAWN, BLACKPAWN,   BLACKPAWN,   BLACKPAWN,  BLACKPAWN, BLACKPAWN,   BLACKPAWN,   BLACKPAWN, '7'},
            {'6', ' ',       ' ',         ' ',         ' ',        ' ',       ' ',         ' ',         ' ',       '6'},
            {'5', ' ',       ' ',         ' ',         ' ',        ' ',       ' ',         ' ',         ' ',       '5'},
            {'4', ' ',       ' ',         ' ',         ' ',        ' ',       ' ',         ' ',         ' ',       '4'},
            {'3', ' ',       ' ',         ' ',         ' ',        ' ',       ' ',         ' ',         ' ',       '3'},
            {'2', WHITEPAWN, WHITEPAWN,   WHITEPAWN,   WHITEPAWN,  WHITEPAWN, WHITEPAWN,   WHITEPAWN,   WHITEPAWN, '2'},
            {'1', WHITEROOK, WHITEKNIGHT, WHITEBISHOP, WHITEQUEEN, WHITEKING, WHITEBISHOP, WHITEKNIGHT, WHITEROOK, '1'},
            {' ', 'A',       'B',         'C',         'D',        'E',       'F',         'G',         'H'}
            // White
    };
    memcpy(Board, original_board, (sizeof(PIECE_T) * 100));
}



void draw_board() {
    setlocale(LC_CTYPE, "");
    for (int i = 0; i < BOARD_ROW_SIZE; i++) {
        for (int j = 0; j < BOARD_COL_SIZE; ++j) {
            wchar_t ch = Board[i][j];
            wprintf(L" %lc ", ch);
        }
        wprintf(L"\n");
    }
}



