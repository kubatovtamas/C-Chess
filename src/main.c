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

/*********************************************** Declarations ***********************************************/

void play_game();

void get_input_game_choice(Game *game);

void get_input_saved_to(char *save_to, int size);

void get_input_prompted(char *save_to, char* prompt, int size);

bool get_input_confirm_choice(char* prompt);

void get_input_names();

bool get_input_accept_draw();

void get_input_save_game();

bool get_input_load_game();



void print_menu_main();

void print_menu_move();

void print_menu_winner();

void print_menu_options();

void print_menu_saved_games();


bool is_valid_tile_from(char *input, bool *back, int *castling);

bool is_valid_tile_to(char *input, bool *back);

long parse_input_to_long();

void offer_draw();

void forfeit();



/********************************************** Not implemented yet ***********************************************/



bool is_checked();

bool can_transform();

void transform_piece();

bool get_input_piece_to_transform();

bool is_revivable_piece();

void get_input_tranform_piece();

/*********************************************** Globals ***********************************************/

bool In_Menu = true;
bool Playing = false;
char Player_One_Name[100];
char Player_Two_Name[100];
bool Is_Draw_Offered = false;
int Winner = -1; // -1: none, 0: draw, 1: player1 (white), 2: player2(black)
bool LoadedGame = false;

/*********************************************** Main ***********************************************/

int main() {
    setlocale(LC_CTYPE, "");

    // Main loop outline -Gigi
    while (In_Menu) {
        print_menu_main();

        long input = parse_input_to_long();
        switch (input) {
            case 2: { // LOAD
                system("clear");
                if (!get_input_load_game()) {
                    break;
                }
                LoadedGame = true;
            }
            // FALLTHROUGH
            case 1: { // NEW GAME
//                system("clear");
                In_Menu = false;
                play_game();
                break;
            }

            case 3: { // QUIT GAME
                wprintf(L"Goodbye!\n");
                In_Menu = false;
                break;
            }
            default:
                break;
        }
    }
    return 0;
}

/*********************************************** Play Game ***********************************************/

void play_game() {
    Game *game = game_start();
    if (!game) {
        wprintf(L"Failed to allocate memory for game.\n");
        return;
    }

    system("clear");
    if (!LoadedGame) {
        get_input_names();
    }

    Playing = true;
    while (Playing) {
        // If draw or either player won, exit main loop
        if (Winner != -1) {
            Playing = false;
        }
        get_input_game_choice(game);
    }
    print_menu_winner();
    game_end(game);
}

/*********************************************** Game Choice ***********************************************/

void get_input_game_choice(Game *game) {
    bool valid_choice = false;
    while (!valid_choice) {
        print_menu_move();
        if (Winner != -1) {
            break;
        }
        long input = parse_input_to_long();
        switch (input) {
            case 1: // MOVE
                valid_choice = true;
                bool back = false;
                int castling = 0;       // 0: none, 1: kingside, 2: queenside
                char from[20], to[20];

                // Prompt: from (or castling, or back)
                while (!back && !is_valid_tile_from(from, &back, &castling));
                if (castling == 1) {
                    castle_kingside(game);
                } else if (castling == 2) {
                    castle_queenside(game);
                } else {
                    // Prompt: to (or back)
                    while (!back && !is_valid_tile_to(to, &back));
                    // Move
                    if (!back) {
                        move(game, from, to);
                        //  ide jöhet: transform_piece()
                        //  if (enemys row && your pawn)
                        //      do while ( !(valid piece input && is_revivable_piece) )
                        //          prompt_for_transform()
                        //      transform_piece()
                    }
                }
                system("clear");
                draw_board();
                break;

            case 2: // UNDO
                valid_choice = true;

                if (get_input_confirm_choice("SURE? Y/N")) {
                    undo(game);
                }
                break;

            case 3: // DRAW
                valid_choice = true;

                if (get_input_confirm_choice("SURE? Y/N")) {
                    offer_draw();
                }
                break;

            case 4: // FORFEIT
                valid_choice = true;

                if (get_input_confirm_choice("SURE? Y/N")) {
                    forfeit();
                }
                break;

            case 5: // SAVE
                valid_choice = true;

                if (get_input_confirm_choice("SURE? Y/N")) {
                    get_input_save_game();
                }
                break;

            case 6: // BACK TO MAIN
                valid_choice = true;
                if (get_input_confirm_choice("SURE? Y/N")) {
                    reset_board();

                    Playing = false;
                    In_Menu = true;
                    memset(Player_One_Name,0,strlen(Player_One_Name));
                    memset(Player_Two_Name,0,strlen(Player_Two_Name));
                    Is_Draw_Offered = false;
                    Round_Count = 0;
                    LoadedGame = false;

                    system("clear");
                }
                break;
            default:
                system("clear");
        }
    }
}


/*********************************************** Implementations ***********************************************/

/*
 * Clear the terminal and print the main menu.
 */
void print_menu_main() {
    system("clear");
    wprintf(L"1. New Game\n");
    wprintf(L"2. Load Game\n");
    wprintf(L"3. Quit\n");
}

/*
 * Draw the board and print the move selection menu.
 */
void print_menu_move() {
    system("clear");
    draw_board();
    wprintf(L"Round: %d. %s's %s turn. ", Round_Count + 1,
            get_current_turn_color() == WHITE ? Player_One_Name : Player_Two_Name,
            get_current_turn_color() == WHITE ? "(WHITE)" : "(BLACK)");

    if (Is_Draw_Offered) {
        get_input_accept_draw();
    } else {
        print_menu_options();
    }
}

/*
 * Calls get_input_saved_to, parses the string
 * return a long from the beginning of the string
 */
long parse_input_to_long() {
    char input[10];
    get_input_saved_to(input, 10);
    char *input_string_part;
    return strtol(input, &input_string_part, 10);
}

/*
 * Use this for user input, it's hard(er) to break.
 * Store user input from stdin to save_to,
 * with a set max buffer size.
 * Deletes residue whitespace.
 */
void get_input_saved_to(char *save_to, int size) {
    fgets(save_to, size, stdin);
    unsigned long len = strlen(save_to);
    if (len > 0 && save_to[len - 1] == '\n')
        save_to[len - 1] = '\0';
}

/*
 * Calls get_input_saved_to.
 * Plus displays a prompt to the terminal.
 */
void get_input_prompted(char *save_to, char* prompt, int size) {
    wprintf(L"%s\n", prompt);
    get_input_saved_to(save_to, size);
}

/*
 * Calls get_input_prompted.
 * Repeats until valid input is given.
 * Only the first character matters, case insensitive.
 * Returns true if answer is yes.
 * Returns false if answer is no.
 */
bool get_input_confirm_choice(char* prompt) {
    char save_to[10];
    int first_letter_insensitive;
    do {
        get_input_prompted(save_to, prompt, 10);
        first_letter_insensitive = tolower(save_to[0]);
    } while (!(first_letter_insensitive == 'y' || first_letter_insensitive == 'n'));

    if (first_letter_insensitive == 'y') {
        return true;
    } else {
        return false;
    }
}

void get_input_save_game() {
    char input_save_name[100];
    char file_name[100] = "";
    get_input_prompted(input_save_name, "Save game as: ", 80);
    strcpy(file_name, "Saved_Games/");
    strcat(file_name, input_save_name);

    save_to_file(file_name, Round_Count, Player_One_Name, Player_Two_Name);
}
/*
 * does this get included
 */
bool get_input_load_game() {
    char input_load_name[100];
    print_menu_saved_games();
    get_input_prompted(input_load_name, "\nLoad file: ", 80);
    return load_from_file(input_load_name, &Round_Count, Player_One_Name, Player_Two_Name, Board);
}

void print_menu_saved_games() {
    wprintf(L"Saved games:\n");
//    system("ls -1 ../../Saved_Games"); // DEBUG MODE
    system("ls -1 Saved_Games"); // PROD MODE
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
bool is_valid_tile_from(char *input, bool *back, int *castling) {
    // Input prompt
    bool kingside = can_castle_kingside();
    bool queenside = can_castle_queenside();
    if (kingside && queenside) {
        wprintf(L"FROM (A1-H8) or BACK or KINGSIDE or QUEENSIDE to castle: \n");
    } else if (kingside) {
        wprintf(L"FROM (A1-H8) or BACK or KINGSIDE to castle: \n");
    } else if (queenside) {
        wprintf(L"FROM (A1-H8) or BACK or QUEENSIDE to castle: \n");
    } else {
        wprintf(L"FROM (A1-H8) or BACK: \n");
    }
    get_input_saved_to(input, 20);

    // If input == BACK (case insensitive)
    if (strcasecmp(input, "back") == 0) {
        system("clear");
        *back = true;
        return false;
    }

    // If input == KINGSIDE (case insensitive)k
    if (strcasecmp(input, "kingside") == 0 && kingside) {
        system("clear");
        *castling = 1;
        return true;
    }

    // If input == QUEENSIDE (case insensitive)
    if (strcasecmp(input, "queenside") == 0 && queenside) {
        system("clear");
        *castling = 2;
        return true;
    }

    // If input == valid tile (own piece)
    if ('a' <= tolower(input[0]) && tolower(input[0]) <= 'h' &&
        1 <= (input[1] - '0') && (input[1] - '0') <= 8) {
        if (check_if_own_piece(convert_tile_number_to_int(input[1]), convert_tile_letter_to_int(input[0]))) {
            return true;
        }
    }

    wprintf(L"That is not a valid input, or that is not your piece. \n");
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
bool is_valid_tile_to(char *input, bool *back) {
    // Input p  rompt
    wprintf(L"TO (A1-H8) or BACK: \n");
    get_input_saved_to(input, 10);

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
            wprintf(L"That's your own piece. \n");
        }
    }
    return false;
}

/*********************************************** NEW FUNCTIONS ***************************************************/

void get_input_names() {
    wprintf(L"Enter Player1's name (WHITE): ");
    get_input_saved_to(Player_One_Name, 100);

    wprintf(L"\nEnter Player2's name (BLACK): ");
    get_input_saved_to(Player_Two_Name, 100);
}

/*
 * Sets the global Is_Draw_Offered variable to true.
 * This will trigger an acceptation input from the opponent.
 */
void offer_draw() {
    Round_Count++;
    Is_Draw_Offered = true;
}

/*
 * Takes a Yes/No input from the user.
 * If yes is provided, game ends with draw.
 * If no is provided, game continues.
 */
bool get_input_accept_draw() {
    wprintf(L"%s %s offered a draw. \n", get_current_turn_color() == WHITE ? Player_Two_Name : Player_One_Name,
            get_current_turn_color() == WHITE ? "(BLACK)" : "(WHITE)");

    if (get_input_confirm_choice("Do you accept? Y/N")) {
        Is_Draw_Offered = false;
        Winner = 0;
    } else {
        Is_Draw_Offered = false;
        Round_Count++;
    }

}

/*
 * Sets the global Winner variable, opponent wins
 */
void forfeit() {
    if (get_current_turn_color() == WHITE) {
        Winner = 2;
    } else {
        Winner = 1;
    }
}


/*
 * Prints the result of the game at the end.
 */
void print_menu_winner() {
    if (Winner == 0) {
        wprintf(L"It's a draw.\n");
    } else if (Winner == 1) {
        wprintf(L"%s (WHITE) wins.\n", Player_One_Name);
    } else if (Winner == 2) {
        wprintf(L"%s (BLACK) wins.\n", Player_Two_Name);
    }
}

/*
 * Prints the options you have in a round.
 */
void print_menu_options() {
    wprintf(L"Enter choice: \n");
    wprintf(L"1. MOVE \n");
    wprintf(L"2. UNDO \n");
    wprintf(L"3. OFFER DRAW \n");
    wprintf(L"4. FORFEIT MATCH \n");
    wprintf(L"5. SAVE MATCH \n");
    wprintf(L"6. BACK TO MAIN MENU \n");
}

bool is_checked();

bool can_transform();

void transform_piece();

bool get_input_piece_to_transform();

bool is_revivable_piece();

void get_input_tranform_piece();
