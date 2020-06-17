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

bool valid_tile_from(char *input, bool *back);

bool valid_tile_to(char *input, bool *back);

void really_prompt(char *really);

bool get_confirmation();

long parse_input_to_long();
/*****************************************************************************************************************/

bool InMenu = true;
bool Playing = false;
//char GameChoice[10];
//COLOR PlayerColor = WHITE;
extern int round_count;

/*****************************************************************************************************************/

int main() {
    setlocale(LC_CTYPE, "");

    // Main loop outline -Gigi
    while (InMenu) {
        print_main_menu();
        long input = parse_input_to_long();
        switch (input) {
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
            default:
                break;
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
            change_state();
        }
    }
}

void get_choice() {
    bool valid_choice = false;
    while (!valid_choice) {
        print_move_menu();

        // Take user input, parse it to number.
        long input = parse_input_to_long();
        switch (input) {

            case 1:
                // MOVE
                valid_choice = true;
                bool back = false;
                char from[10], to[10];

                while (!back && !valid_tile_from(from, &back));     /* Take user input until valid FROM tile */
                while (!back && !valid_tile_to(to, &back));         /* AND valid TO tile is provided.        */
                if (!back) {                                        /* Setting the back flag to true         */
                    move(from, to);                                 /* terminates the input prompt loop      */
                }

                system("clear");
                draw_board();
                break;

            case 2:
                // UNDO
                valid_choice = true;

                if (get_confirmation()) {
                    wprintf(L"YES BRANCH\n");
                } else {
                    wprintf(L"NO BRANCH\n");
                }
                break;

            case 3:
                // DRAW
                valid_choice = true;

                if (get_confirmation()) {
                    wprintf(L"YES BRANCH\n");
                } else {
                    wprintf(L"NO BRANCH\n");
                }
                break;

            case 4:
                // FORFEIT
                valid_choice = true;

                if (get_confirmation()) {
                    wprintf(L"YES BRANCH\n");
                } else {
                    wprintf(L"NO BRANCH\n");
                }
                break;

            case 5:
                // SAVE
                valid_choice = true;
                break;

            case 6:
                // BACK TO MAIN
                valid_choice = true;
                if (get_confirmation()) {
                    wprintf(L"YES BRANCH\n");

                    reset_board();
                    Playing = false;
                    InMenu = true;
                    system("clear");
                } else {
                    wprintf(L"NO BRANCH\n");
                }
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
    wprintf(L"Round: %d. %s's turn. ", round_count + 1, get_current_turn_color() == WHITE ? "WHITE" : "BLACK");
    wprintf(L"Enter choice: \n");
    wprintf(L"1. MOVE \n");
    wprintf(L"2. UNDO \n");
    wprintf(L"3. OFFER DRAW \n");
    wprintf(L"4. FORFEIT MATCH \n");
    wprintf(L"5. SAVE MATCH \n");
    wprintf(L"6. BACK TO MAIN MENU \n");
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
 * Calls get_input, parses the string
 * return a long from the beginning of the string
 */
long parse_input_to_long() {
    char input[10];
    get_input(input, 10);
    char *input_string_part;
    return strtol(input, &input_string_part, 10);
}

/*
 * Prompt the users for Y/N answer.
 */
void really_prompt(char *really) {
    wprintf(L"SURE? Y/N\n");
    get_input(really, 10);
}

/*
 * Calls really_prompt.
 * Repeats until valid input is given.
 * Only the first character matters, case insensitive.
 * Returns true if answer is yes.
 * Returns false if answer is no.
 */
bool get_confirmation() {
    char really[10];
    char first_letter_insensitive;
    do {
        really_prompt(really);
        first_letter_insensitive = tolower(really[0]);
    } while (!(first_letter_insensitive == 'y' || first_letter_insensitive == 'n'));

    if (first_letter_insensitive == 'y') {
        return true;
    } else {
        return false;
    }
}

/*
 * Validator for FROM tile.
 * Returns true IF
 * matches the [A-Ha-h][1-9] regex,
 * AND
 * is the player's own piece.
 *
 * Sets the provided bool pointer to true for navigating
 * back in the menu. Returns false in this case.
 */
bool valid_tile_from(char *input, bool *back) {
    // Input prompt
    wprintf(L"FROM (A1-H8) or BACK: \n");
    get_input(input, 10);

    // If input == back (case insensitive)
    if (strcasecmp(input, "back") == 0) {
        system("clear");
        *back = true;
        return false;
    }

    // If input == valid tile (own piece)
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
 *
 * Sets the provided bool pointer to true for navigating
 * back in the menu. Returns false in this case.
 */
bool valid_tile_to(char *input, bool *back) {
    // Input prompt
    wprintf(L"TO (A1-H8) or BACK: \n");
    get_input(input, 10);

    // If input == back (case insensitive)
    if (strcasecmp(input, "back") == 0) {
        system("clear");
        *back = true;
        return false;
    }

    // If input == valid tile (not own piece)
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

