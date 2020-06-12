//
// Created by gigi on 6/12/20.
//

#include<stdio.h>
#include<wchar.h>
#include<locale.h>
#include "sakk.h"

wchar_t Board[8][8] = {
// Black on top for now
// top row
{BLACKROOK, BLACKKNIGHT, BLACKBISHOP, BLACKQUEEN, BLACKKING, BLACKBISHOP, BLACKKNIGHT, BLACKROOK},
{BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN, BLACKPAWN},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
{WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN, WHITEPAWN},
{WHITEROOK, WHITEKNIGHT, WHITEBISHOP, WHITEQUEEN, WHITEKING, WHITEBISHOP, WHITEKNIGHT, WHITEROOK}
};

void drawBoard() {
    for (int i = 0; i < 8; ++i) {
        setlocale(LC_CTYPE, "");
        for (int j = 0; j < 8; ++j) {
            wchar_t ch = Board[i][j];
            wprintf(L" %lc ", ch);
        }
        wprintf(L"\n");
    }
}