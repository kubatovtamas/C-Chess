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

bool inmenu = true;
bool playing = false;
char GameChoice[10];
COLOR playerColor = WHITE;

bool valid_position(const char *input);
bool valid_move(const char *input);
void playGame();
void getChoice();
bool piece_is_color(int row, int col);

int main() {
    setlocale(LC_CTYPE, "");

    // Main loop outline -Gigi
    while (inmenu) {
        // print menu
        wprintf(L"1. New Game\n");
        wprintf(L"2. Load Game\n");
        wprintf(L"3. Quit\n");
//        wprintf(L"\n");

        fgets(GameChoice, 10, stdin);
        unsigned long len = strlen(GameChoice);
        if (len > 0 && GameChoice[len-1] == '\n')
            GameChoice[len-1] = '\0';

        switch (atoi(GameChoice)) {
            case 1: {
                wprintf(L"Starting...\n");
                playGame();
                break;
            }
            case 2: {
                wprintf(L"Loading...\n");
                break;
            }
            case 3: {
                wprintf(L"Goodbye!\n");
                inmenu = 0;
                break;
            }
            default: wprintf(L"I'm sorry, what was that?\n");
                break;
        }
    }

    return 0;
}

void playGame() {
    playing = true;
    while(playing) {
        drawBoard();
        getChoice();
        step();
    }
}

void getChoice() {
    bool valid_choice = false;

    while (!valid_choice) {
        char input[10];

        wprintf(L"Enter choice: \n");
        wprintf(L"1. MOVE \n");
        wprintf(L"2. OFFER DRAW \n");
        wprintf(L"3. FORFEIT MATCH \n");
        wprintf(L"4. SAVE MATCH \n");
        wprintf(L"5. BACK TO MAIN MENU \n");
        fgets(input, 10, stdin);
        unsigned long len = strlen(GameChoice);
        if (len > 0 && GameChoice[len-1] == '\n')
            GameChoice[len-1] = '\0';

        switch (atoi(input)) {
            case 1:
                valid_choice = true;
                wprintf(L"CASE1\n");
                break;
            case 2:
                valid_choice = true;
                wprintf(L"CASE2\n");
                break;
            case 3:
                valid_choice = true;
                wprintf(L"CASE3\n");
                break;
            case 4:
                valid_choice = true;
                wprintf(L"CASE4\n");
                break;
            case 5:
                valid_choice = true;
                wprintf(L"CASE5\n");
                break;
            default:
                wprintf(L"default\n");
        }
    }
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
    if (playerColor == WHITE) {
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