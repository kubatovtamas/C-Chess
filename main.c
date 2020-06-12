//
// Created by kuba on 6/12/20.
//
#include<stdio.h>
#include<wchar.h>
#include<locale.h>

int inmenu = 1;
int playing = 0;
int inp = 0;

int main() {
    // pseudo-code:
    // while inmenu
    //      1. New Game
    //             Get player name
    //      2. Load Game
    //      3. Quit
    // while playing
    //      GetNext Step
    // - Gigi
   while (inmenu) {
        printf("1. New Game\n");
        printf("2. Load Game\n");
        printf("3. Quit\n");
        printf("\n");
        scanf("%d", &inp);

        switch (inp) {
            case 1: printf("Starting...\n"); break;
            case 2: printf("Loading...\n"); break;
            case 3: {
                printf("Goodbye!\n");
                inmenu = 0;
                break;
            }
            default: printf("I'm sorry, what was that?\n");
                break;
        }
   }

    setlocale(LC_CTYPE, "");
    for (int i = 0; i < 12; ++i) {
        wchar_t ch = (0x2654 + i);
        wprintf(L"%lc\n", ch);
    }


    return 0;
}