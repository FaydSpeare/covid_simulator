#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"


void init_state(state* state, parameters* params) {

    state->time_step = 0;
    state->population = (person*) malloc(sizeof(person) * params->pop_size);

    for (int i = 0; i < params->pop_size; i++) {
        state->population[i] = (person) {
            .infected = 0,
            .infected_time = 0,
            .diagnosed = 0
        };
    }

}


void run_simulation(parameters* params) {

    state s;
    init_state(&s, params);

    for (int i = 0; i < params->time_steps; i++) {

        step(&s, params);

    }

}


int main() {
    printf("Hello, World!\n");

    parameters params = {
            .pop_size = 100,
            .time_steps = 10,
            .r0 = 2.11
    };

    run_simulation(&params);
    return 0;
}


