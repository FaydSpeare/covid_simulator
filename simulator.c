//
// Created by fayd on 6/11/20.
//

#include <stdio.h>

#include "simulator.h"

void step(state* s, parameters* params) {
    s->time_step++;
    printf("Time Step: %d\n", s->time_step);
}
