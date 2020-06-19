//
// Created by gigi on 6/14/20.
//

#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>         // memcpy
#include <ctype.h>          // tolower
#include <stdio.h>

#include "board.h"
#include "piece.h"
#include "game.h"

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

bool has_moved_white_king = false;              // D1
bool has_moved_white_rook_queenside = false;    // A1
bool has_moved_white_rook_kingside = false;     // H1

bool has_moved_black_king = false;              // D8
bool has_moved_black_rook_queenside = false;    // A8
bool has_moved_black_rook_kingside = false;     // H8

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


/*
 * Resets the board to the starting state.
 * Overwrites the memory of the starting Board.
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

/*
 * Takes two string args, in the form of "A1"/"D4"/"g7". (case insensitive)
 * Mutates the Board accordingly. Increments the global Round_Count.
 *
 * Converter functions handle the proper conversions from str to int.
 * The letter is responsible for the second,
 * The number is responsible for the first
 * array selector.
 *
 * Eg.  D2 -> Board[7][4]
 *      D4 -> Board[5][4]
 */
bool move(Game *game, char *from, char *to) {
    int from_letter = convert_tile_letter_to_int(from[0]);
    int from_number = convert_tile_number_to_int(from[1]);
    int to_letter = convert_tile_letter_to_int(to[0]);
    int to_number = convert_tile_number_to_int(to[1]);

    // Game Data Before
    //char *tiles[4] = {from, to, NULL, NULL};
    int fromTile[2] = { from_letter, from_number };
    int toTile[2] = { to_letter, to_number };
    PIECE_T before[2] = {Board[from_number][from_letter], Board[to_number][to_letter]};

    // Move
    Board[to_number][to_letter] = Board[from_number][from_letter]; // to set
    Board[from_number][from_letter] = ' '; // from set
    Round_Count++;

    // Game Data After
    PIECE_T after[2] = {Board[from_number][from_letter], Board[to_number][to_letter]};

    move_after_undo(game, displayed_game_state_ptr);

    // save move to game_state
    Game_State_Data *game_state_data = new_game_state_data(fromTile, toTile, before, after);
    new_game_state(game, game_state_data);

    debug_print_game(game);

}


void undo(Game *game) {

    if (!displayed_game_state_ptr->previous) { return; }

//    char *from = (displayed_game_state_ptr->data->tiles)[0];      // { from, to, NULL, NULL };
//    char *to = displayed_game_state_ptr->data->tiles[1];        // { from, to, NULL, NULL };

//    int from_letter = convert_tile_letter_to_int(from[0]);
//    int from_number = convert_tile_number_to_int(from[1]);
//    int to_letter = convert_tile_letter_to_int(to[0]);
//    int to_number = convert_tile_number_to_int(to[1]);

    // this is a little hairy
    int to_letter = displayed_game_state_ptr->data->toTile[0];
    int to_number = displayed_game_state_ptr->data->toTile[1];

    int from_letter = displayed_game_state_ptr->data->fromTile[0];
    int from_number = displayed_game_state_ptr->data->fromTile[1];

    PIECE_T originalFromPiece = (displayed_game_state_ptr->data->before)[0];        // e.g ['pawn', 'queen'] if pawn hit queen
    PIECE_T originalToPiece = (displayed_game_state_ptr->data->before)[1];

    // Change board accordingly
    Board[to_number][to_letter] = originalToPiece;
    Board[from_number][from_letter] = originalFromPiece;

    // Change round count to reflect undo
    Round_Count--;

    //debug_print_game(game);

    undo_to_previous_state();

    debug_print_game(game);

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
int convert_tile_number_to_int(char ch) {

    return 9 - (ch - '0');
}