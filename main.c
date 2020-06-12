//
// Created by kuba on 6/12/20.
//
#include<stdio.h>
#include<wchar.h>
#include<locale.h>

#include "sakk.h"

int inmenu = 1;
int playing = 0;
int inp = 0;

int main() {
    setlocale(LC_CTYPE, "");

    // Main loop outline -Gigi
   while (inmenu) {
       // print menu
        wprintf(L"1. New Game\n");
        wprintf(L"2. Load Game\n");
        wprintf(L"3. Quit\n");
        wprintf(L"\n");

        scanf("%d", &inp);          // get user input

        switch (inp) {
            case 1: {
                wprintf(L"Starting...\n");
                drawBoard();
                break;
            }
            case 2: wprintf(L"Loading...\n"); break;
            case 3: {
                wprintf(L"Goodbye!\n");
                inmenu = 0;
                break;
            }
            default: wprintf(L"I'm sorry, what was that?\n");
                break;
        }
   }

   // original unicode testing
/*
    for (int i = 0; i < 12; ++i) {
        wchar_t ch = (0x2654 + i);
        wprintf(L"%lc\n", ch);
    }
*/

    return 0;
}