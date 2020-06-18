//
// Created by gigi on 6/12/20.
//

#include "libsakk.h"
#include <stdlib.h>

int round_count = 0;        // global

/*
 * ¯\_(ツ)_/¯
 */
//bool is_even(int n) {
//    return (n % 2 == 0);
//}

// TODO Head needs to always point to state 0 with the default board
const struct State *defaultstate = NULL;
struct State *laststate = NULL;

// insert a link to the new state to the end of the list
// - Gigi
void change_state() {
//    wprintf(L"Step function.\n");
//   struct State *newstate = (struct State*) malloc(sizeof(struct State));       //create a link
//   //newstate->key = key;                       // TODO implement current key++
//   // TODO save data
//
//   // Our struct will never be empty in this case
//    laststate->next = newstate;
//    newstate->previous = laststate;
//    laststate = newstate;
//
//    free(newstate); // not using this yet
}
