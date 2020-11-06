#include <stdlib.h>

#include "simulator.h"

void init_params(parameters* params) {
    params->pop_size = 100;
    params->time_steps = 10;
    params->r0 = 4.11;
    params->death_rate = 0.01;
    params->recover_time = 10;
    params->infected0 = 1;
}


void init_state(state* state, parameters* params) {

    state->time_step = 0;
    state->population = (person*) malloc(sizeof(person) * params->pop_size);

    for (int i = 0; i < params->pop_size; i++) {
        state->population[i] = (person) {
            .infected = 0,
            .infected_time = 0,
            .diagnosed = 0,
            .has_been_infected = 0,
            .has_infected = 0
        };
    }

    for (int i = 0; i < params->infected0; i++) {
        state->population[i].infected = 1;
        state->population[i].has_been_infected = 1;
    }

}


void run_simulation() {

    parameters params;
    state s;

    init_params(&params);
    init_state(&s, &params);

    for (int i = 0; i < params.time_steps; i++) {
        step(&s, &params);
    }

}


int main() {
    run_simulation();
    return 0;
}


