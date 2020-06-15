//
// Created by kuba on 6/12/20.
//

#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "libsakk.h"

/*****************************************************************************************************************/

//bool valid_position(const char *input);

//bool valid_move(const char *input);

void play_game();

void get_choice();

void get_input(char *str, int size);

void print_main_menu();

void print_move_menu();

bool move(char *from, char *to);

int convert_tile_letter_to_int(char ch);

int convert_tile_number_to_int(char ch);

bool is_even(int n);

bool valid_tile_from(char *input);

bool valid_tile_to(char *input);

void reset_board();
/*****************************************************************************************************************/

bool InMenu = true;
bool Playing = false;
char GameChoice[10];
//COLOR PlayerColor = WHITE;
extern int round_count;

/*****************************************************************************************************************/

int main() {
    setlocale(LC_CTYPE, "");

    // Main loop outline -Gigi
    while (InMenu) {
        print_main_menu();
        get_input(GameChoice, 10);
        switch (atoi(GameChoice)) {
            case 1: {
                system("clear");
                InMenu = false;
                play_game();
                break;
            }
            case 2: {
                system("clear");
                // load_from_file()
                break;
            }
            case 3: {
                wprintf(L"Goodbye!\n");
                InMenu = false;
                break;
            }
        }
    }

    return 0;
}

/*****************************************************************************************************************/

void play_game() {
    Playing = true;
    while (Playing) {
        system("clear");
        get_choice();
        if (!InMenu) {
            step();
        }
    }
}

void get_choice() {
    bool valid_choice = false;
    while (!valid_choice) {
        print_move_menu();

        char input[10];
        get_input(input, 10);

        switch (atoi(input)) {
            case 1:
                // MOVE
                valid_choice = true;
                char from[10];
                char to[10];
                /*
                 * Take user input until
                 * valid FROM tile and
                 * valid TO tile is provided.
                 */
                while (!valid_tile_from(from));
                while (!valid_tile_to(to));
                move(from, to);

                system("clear");
                draw_board();
                break;
            case 2:
                // UNDO
                valid_choice = true;
                break;
            case 3:
                // DRAW
                valid_choice = true;
                break;
            case 4:
                // FORFEIT
                valid_choice = true;
                break;
            case 5:
                // SAVE
                valid_choice = true;
                break;
            case 6:
                // BACK TO MAIN
                valid_choice = true;
                reset_board();
                Playing = false;
                InMenu = true;
                system("clear");
                break;
            default:
                system("clear");
        }
    }
}

/*
 * Clear the terminal and print the main menu.
 */
void print_main_menu() {
    system("clear");
    wprintf(L"1. New Game\n");
    wprintf(L"2. Load Game\n");
    wprintf(L"3. Quit\n");
}

/*
 * Draw the board and print the move selection menu.
 */
void print_move_menu() {
    draw_board();
    wprintf(L"Round: %d. %s's turn. ", round_count + 1, is_even(round_count) ? "WHITE" : "BLACK");
    wprintf(L"Enter choice: \n");
    wprintf(L"1. MOVE \n");
    wprintf(L"2. UNDO \n");
    wprintf(L"3. OFFER DRAW \n");
    wprintf(L"4. FORFEIT MATCH \n");
    wprintf(L"5. SAVE MATCH \n");
    wprintf(L"6. BACK TO MAIN MENU \n");
}

/*
 * Returns true if in a given round, Board[row][col]
 * is the current players own piece.
 * Returns false otherwise.
 */
bool check_if_own_piece(int row, int col) {
    // WHITE
    if (is_even(round_count)) {
        switch (Board[row][col]) {
            case WHITEPAWN:
            case WHITEKNIGHT:
            case WHITEBISHOP:
            case WHITEROOK:
            case WHITEQUEEN:
            case WHITEKING:
                return 1;
            default:
                return 0;
        }
    }
    // BLACK
    else {
        switch (Board[row][col]) {
            case BLACKPAWN:
            case BLACKKNIGHT:
            case BLACKBISHOP:
            case BLACKROOK:
            case BLACKQUEEN:
            case BLACKKING:
                return 1;
            default:
                return 0;
        }
    }
}

/*
 * Use this for user input, it's hard(er) to break.
 * Store user input from stdin to str,
 * with a set max buffer size.
 * Deletes residue whitespace.
 */
void get_input(char *str, int size) {
    fgets(str, size, stdin);
    unsigned long len = strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
}

/*
 * ¯\_(ツ)_/¯
 */
bool is_even(int n) {
    return (n % 2 == 0);
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
bool move(char *from, char *to) {
    int from_letter = convert_tile_letter_to_int(from[0]);
    int from_number = convert_tile_number_to_int(from[1]);
    int to_letter = convert_tile_letter_to_int(to[0]);
    int to_number = convert_tile_number_to_int(to[1]);

    Board[to_number][to_letter] = Board[from_number][from_letter]; // to set
    Board[from_number][from_letter] = ' '; // from set
    round_count++;
}

/*
 * Validator for FROM tile.
 * Returns true IF
 * matches the [A-Ha-h][1-9] regex,
 * AND
 * is the player's own piece.
 */
bool valid_tile_from(char *input) {
    wprintf(L"FROM (A1-H8): \n");
    get_input(input, 10);
    if ('a' <= tolower(input[0]) && tolower(input[0]) <= 'h' &&
        1 <= (input[1] - '0') && (input[1] - '0') <= 8) {
        if (check_if_own_piece(convert_tile_number_to_int(input[1]), convert_tile_letter_to_int(input[0]))) {
            return true;
        }
    }
    wprintf(L"That is not your piece. \n");
    return false;
}

/*
 * Validator for TO tile.
 * Returns true IF
 * matches the [A-Ha-h][1-9] regex,
 * AND
 * is NOT the player's own piece.
 */
bool valid_tile_to(char *input) {
    wprintf(L"TO (A1-H8): \n");
    get_input(input, 10);
    if ('a' <= tolower(input[0]) && tolower(input[0]) <= 'h' &&
        1 <= (input[1] - '0') && (input[1] - '0') <= 8) {
        if (!check_if_own_piece(convert_tile_number_to_int(input[1]), convert_tile_letter_to_int(input[0]))) {
            return true;
        } else {
            wprintf(L"That your own piece. \n");
        }
    }
    return false;
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

/*
 * Resets the board to the starting state.
 * Overwrites the memory of the starting Board,
 * so it may not be okay for long term use
 * (as we don't have functionality for saving Rounds/Steps)
 */
void reset_board() {
    PIECE_T original_board[BOARD_ROW_SIZE][BOARD_COL_SIZE] = {
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
    memcpy(Board, original_board, (sizeof(PIECE_T) * 100));
}