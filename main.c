//
// Created by kuba on 6/12/20.
//
#include <stdio.h>
#include <wchar.h>
#include <locale.h>
#include <ctype.h>
#include <string.h>

#include "libsakk.h"

_Bool inmenu = 1;
_Bool playing = 0;
int GameChoice = 0;
COLOR playerColor = WHITE;

_Bool valid_position(const char *input);
_Bool valid_move(const char *input);
void playGame();
void getChoice();
_Bool piece_is_color(int row, int col);

int main() {
    setlocale(LC_CTYPE, "");

    // Main loop outline -Gigi
    while (inmenu) {
        // print menu
        wprintf(L"1. New Game\n");
        wprintf(L"2. Load Game\n");
        wprintf(L"3. Quit\n");
        wprintf(L"\n");

        scanf("%d", &GameChoice);          // get user GameChoice

        switch (GameChoice) {
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
    _Bool playing = 1;
    while(playing) {
        drawBoard();
        getChoice();
        step();
    }
}

void getChoice() {
    _Bool choice = 0;

    while (!choice) {
        char input[2];

        wprintf(L"Please enter the position of the piece you would like to move: ");
        scanf("%s", &input);

        if (valid_move(input)) { choice = 1; }
    }
}

_Bool valid_move(const char *input) {
    if (strlen(input) < 2) {
        return 0;
    }

    int col = (tolower(input[0]) - 'a') - 1;
    int row = input[1] - '0' - 1;

    // valid range
    if ( col < 0 || col >= 8
        && row < 0 || col >= 8 ) {
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