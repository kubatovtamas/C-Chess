//
// Created by gigi on 6/12/20.
//

#include "libsakk.h"
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

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
