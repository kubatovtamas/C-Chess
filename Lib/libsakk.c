//
// Created by gigi on 6/12/20.
//

#include "libsakk.h"
#include <stdlib.h>

// insert a link to the new state to the end of the list
// - Gigi
void step(struct Board board) {
   struct State *newstate = (struct State*) malloc(sizeof(struct State));       //create a link
   //newstate->key = key;                       // TODO implement current key++
   newstate->state_board = board;

   // Our struct will never be empty in this case
    laststate->next = newstate;
    newstate->previous = laststate;
    laststate = newstate;
}
