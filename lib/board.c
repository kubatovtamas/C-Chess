//
// Created by gigi on 6/14/20.
//

#include <wchar.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>         // memcpy
#include <ctype.h>          // tolower

#include "board.h"
#include "piece.h"
#include "game.h"

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
 * Takes two string args, in the form of for example "A1"/"D4"/"g7". (case insensitive)
 * Mutates the Board accordingly. Increments the global round_count.
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
    char* tiles[4] = { from, to, NULL, NULL };        // Castling not implemented
    PIECE_T before[2] = { Board[from_number][from_letter], Board[to_number][to_letter] };

    // Move
    Board[to_number][to_letter] = Board[from_number][from_letter]; // to set
    Board[from_number][from_letter] = ' '; // from set
    round_count++;

    // Game Data After
    PIECE_T after[2] = { Board[from_number][from_letter], Board[to_number][to_letter] };

    if (displayed_game_state_ptr->next) {
        free_game_state_to_end(displayed_game_state_ptr->next);
    }

    // save move to game_state
    Game_State_Data *game_state_data = new_game_state_data(tiles, before, after);
    new_game_state(game, game_state_data);

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

void undo(Game* game) {

    if (!displayed_game_state_ptr->previous) { return; }

    char* from = (displayed_game_state_ptr->data->tiles)[0];      // { from, to, NULL, NULL };
    char* to = displayed_game_state_ptr->data->tiles[1];        // { from, to, NULL, NULL };

    int from_letter = convert_tile_letter_to_int(from[0]);
    int from_number = convert_tile_number_to_int(from[1]);
    int to_letter = convert_tile_letter_to_int(to[0]);
    int to_number = convert_tile_number_to_int(to[1]);

    PIECE_T originalFromPiece = (displayed_game_state_ptr->data->before)[0];        // e.g ['pawn', 'queen'] if pawn hit queen
    PIECE_T originalToPiece = (displayed_game_state_ptr->data->before)[1];

    // Change board accordingly
    Board[to_number][to_letter] = originalToPiece;
    Board[from_number][from_letter] = originalFromPiece;

    // Change round count to reflect undo
    round_count--;

    undo_to_previous_state(game);

}