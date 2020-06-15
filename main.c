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

bool InMenu = true;
bool Playing = false;
char GameChoice[10];
COLOR PlayerColor = WHITE;

bool valid_position(const char *input);
bool valid_move(const char *input);
void play_game();
void get_choice();
bool piece_is_color(int row, int col);
void get_input(char* str, int size);
void print_main_menu();

void print_move_menu();

int main() {
    setlocale(LC_CTYPE, "");

    // Main loop outline -Gigi
    while (InMenu) {
        print_main_menu();
        get_input(GameChoice, 10);
        switch (atoi(GameChoice)) {
            case 1: {
                system("clear");
                play_game();
                break;
            }
            case 2: {
                system("clear");
                // load_from_file
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

void print_main_menu() {
    system("clear");
    wprintf(L"1. New Game\n");
    wprintf(L"2. Load Game\n");
    wprintf(L"3. Quit\n");
}

void play_game() {
    Playing = true;
    while(Playing) {
        drawBoard();
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
                // GetMove
                valid_choice = true;
                break;
            case 2:
                // Draw
                valid_choice = true;
                break;
            case 3:
                // Forfeit
                valid_choice = true;
                break;
            case 4:
                // Save
                valid_choice = true;
                break;
            case 5:
                valid_choice = true;
                Playing = false;
                InMenu = true;
                system("clear");
                break;
            default:
                wprintf(L"that is not okay, at all\n");
        }
    }
}

void print_move_menu() {
    wprintf(L"Enter choice: \n");
    wprintf(L"1. MOVE \n");
    wprintf(L"2. OFFER DRAW \n");
    wprintf(L"3. FORFEIT MATCH \n");
    wprintf(L"4. SAVE MATCH \n");
    wprintf(L"5. BACK TO MAIN MENU \n");
}

bool valid_move(const char *input) {
    if (strlen(input) < 2) {
        return 0;
    }

    int col = (tolower(input[0]) - 'a') - 1;
    int row = input[1] - '0' - 1;

    // valid range
    if ( (col < 0 || col >= 8) && (row < 0 || col >= 8) ) {
        return 0;
    }

    // valid color
    return piece_is_color(row, col);
}

_Bool piece_is_color(int row, int col) {
    if (PlayerColor == WHITE) {
        switch(Board[row][col]) {
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
    else {      // player is black
        switch(Board[row][col]) {
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
 * Store user input from stdin to str,
 * with a set max buffer size.
 * Deletes residue whitespace.
 */
void get_input(char* str, int size) {
    fgets(str, size, stdin);
    unsigned long len = strlen(str);
    if (len > 0 && str[len-1] == '\n')
        str[len-1] = '\0';
}
