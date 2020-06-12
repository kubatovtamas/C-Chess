//
// Created by kuba on 6/12/20.
//
#include<stdio.h>
#include<wchar.h>
#include<locale.h>

int main() {
    // pseudo-code:
    // while inmenu
    //      1. New Game
    //             Get player name
    //      2. Load Game
    //      3. Quit
    // while playing
    //      GetNext Step
    setlocale(LC_CTYPE, "");
    for (int i = 0; i < 12; ++i) {
        wchar_t ch = (0x2654 + i);
        wprintf(L"%lc\n", ch);
    }
    return 0;
}