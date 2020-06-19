//
// Created by gigi on 6/14/20.
//

#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>         // memcpy

#include "libsakk.h"        // debugging
#include "board.h"
#include "piece.h"
#include "game.h"
#include "position.h"

// Starting Position
PIECE_T Board[BOARD_ROW_SIZE][BOARD_COL_SIZE] = {
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

/*
 * Resets the board to the starting state.
 * Overwrites the memory of the starting Board.
 */
// kuba
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
    memcpy(Board, original_board, (sizeof(PIECE_T) * BOARD_ROW_SIZE * BOARD_COL_SIZE));
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

/******************** CASTLING ****************/
// kuba
bool has_moved_white_king = false;              // D1
bool has_moved_white_rook_queenside = false;    // A1
bool has_moved_white_rook_kingside = false;     // H1

bool has_moved_black_king = false;              // D8
bool has_moved_black_rook_queenside = false;    // A8
bool has_moved_black_rook_kingside = false;     // H8

// kuba
bool can_castle_kingside() {
    if (get_current_turn_color() == WHITE) {
        if (!has_moved_white_king) {
            if (!has_moved_white_rook_kingside) {
                if (Board[8][6] == ' ' && Board[8][7] == ' ') {
                    return true;
                }
            }
        }
        return false;
    } else {
        if (!has_moved_black_king) {
            if (!has_moved_black_rook_kingside) {
                if (Board[1][6] == ' ' && Board[1][7] == ' ') {
                    return true;
                }
            }
        }
        return false;
    }
}

// kuba
bool can_castle_queenside() {
    if (get_current_turn_color() == WHITE) {
        if (!has_moved_white_king) {
            if (!has_moved_white_rook_queenside) {
                if (Board[8][2] == ' ' && Board[8][3] == ' ' && Board[8][4] == ' ') {
                    return true;
                }
            }
        }
        return false;
    } else {
        if (!has_moved_black_king) {
            if (!has_moved_black_rook_queenside) {
                if (Board[1][2] == ' ' && Board[1][3] == ' ' && Board[1][4] == ' ') {
                    return true;
                }
            }
        }
        return false;
    }
}

// kuba
void castle_queenside(Game* game) {
    if (get_current_turn_color() == WHITE) {
        castle(game, "E1", "A1", "C1", "D1");
        has_moved_white_king = true;
        has_moved_white_rook_queenside = true;
    } else {
        castle(game, "E8", "A8", "C8", "D8");
        has_moved_black_king = true;
        has_moved_black_rook_queenside = true;
    }
}

// kuba
void castle_kingside(Game* game) {
    if (get_current_turn_color() == WHITE) {
        castle(game, "E1", "H1", "G1", "F1");
        has_moved_white_king = true;
        has_moved_white_rook_kingside = true;
    } else {
        castle(game, "E8", "H8", "G8", "F8");
        has_moved_black_king = true;
        has_moved_black_rook_kingside = true;
    }
}

// kuba
bool can_transform(int* pos, COLOR* color) {
    if (get_current_turn_color() == BLACK) {
        for (int i = 1; i < 9; ++i) {
            if (Board[1][i] == WHITEPAWN) {
                *color = WHITE;
                *pos = i;
                return true;
            }
        }
        return false;
    } else {
        for (int i = 0; i < 9; ++i) {
            if (Board[8][i] == BLACKPAWN) {
                *color = BLACK;
                *pos = i;
                return true;
            }
        }
        return false;
    }
}


// 50-50
bool castle(Game *game, char *from_king, char *from_rook, char *to_king, char *to_rook) {
    move_after_undo(game, displayed_game_state_ptr);

    //King
    Position_Data* king_fromPosition = convert_to_position_data(from_king);
    Position_Data* king_toPosition = convert_to_position_data(to_king);

    // Rook
    Position_Data* rook_fromPosition = convert_to_position_data(from_rook);
    Position_Data* rook_toPosition = convert_to_position_data(to_rook);

    Game_State_Data* game_state_data = new_game_state_data(king_fromPosition, king_toPosition, rook_fromPosition, rook_toPosition);
    new_game_state(game, game_state_data);

    // move pieces
    mutate_board(from_king, to_king);
    mutate_board(from_rook, to_rook);

    Round_Count++;
}

bool move(Game *game, char *from, char *to) {
    move_after_undo(game, displayed_game_state_ptr);

    Position_Data* from_position = convert_to_position_data(from);
    Position_Data* to_position = convert_to_position_data(to);

    // save move to game_state
    Game_State_Data* game_state_data = new_game_state_data(from_position, to_position, NULL, NULL);
    new_game_state(game, game_state_data);

    mutate_board(from, to);

    // ORDER MATTERS!
    set_has_moved_values(from_position, true);
    Round_Count++;

    debug_print_game(game);
}

void undo(Game *game) {
    if (!displayed_game_state_ptr->previous) { return; }

    // get position data
    Position_Data* from = displayed_game_state_ptr->data->fromPosition;
    Position_Data* to = displayed_game_state_ptr->data->toPosition;

    Board[to->rowNumber][to->colLetter] = to->type;         // set to tile to original to type
    Board[from->rowNumber][from->colLetter] = from->type;   // set from tile to original from type

    // Change round count to reflect undo
    // has to be before set_has_moved_values
    Round_Count--;
    set_has_moved_values(from, false);

    // if Castling
    if (displayed_game_state_ptr->data->fromCastle
        && displayed_game_state_ptr->data->toCastle ) {
        // get position data
        Position_Data* from_castle = displayed_game_state_ptr->data->fromCastle;
        Position_Data* to_castle = displayed_game_state_ptr->data->toCastle;

        Board[to_castle->rowNumber][to_castle->colLetter] = to_castle->type;         // set to tile to original to type
        Board[from_castle->rowNumber][from_castle->colLetter] = from_castle->type;   // set from tile to original from type

        set_has_moved_values(from_castle, false);
    }


    undo_to_previous_state();

    debug_print_game(game);
}



// kuba
bool mutate_board(char *from, char *to) {
    int from_letter = convert_tile_letter_to_int(from[0]);
    int from_number = convert_tile_number_to_int(from[1]);
    int to_letter = convert_tile_letter_to_int(to[0]);
    int to_number = convert_tile_number_to_int(to[1]);

    Board[to_number][to_letter] = Board[from_number][from_letter]; // to set
    Board[from_number][from_letter] = ' '; // from set
}

// kuba
void reset_has_moved_values() {

        has_moved_white_king = false;              // D1
        has_moved_white_rook_queenside = false;    // A1
        has_moved_white_rook_kingside = false;     // H1

        has_moved_black_king = false;              // D8
        has_moved_black_rook_queenside = false;    // A8
        has_moved_black_rook_kingside = false;     // H8

}