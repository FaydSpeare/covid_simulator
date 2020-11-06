#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"

void print_array(int* arrray, int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%d ", arrray[i]);
    }
    printf("]\n");
}

void print_counts(parameters* params, state* s) {
    print_array(s->susceptible_counts, params->time_steps);
    print_array(s->infected_counts, params->time_steps);
    print_array(s->deceased_counts, params->time_steps);
    print_array(s->recovered_counts, params->time_steps);
    print_array(s->diagnosed_counts, params->time_steps);
}

void init_params(parameters* params) {
    params->pop_size = 100;
    params->time_steps = 500;
    params->r0 = 4.11;
    params->r0_diagnosed = 1.0;
    params->death_rate = 0.001;
    params->recover_time = 10;
    params->infected0 = 5;
    params->test_rate = 0.1;
}

void run_simulation() {

    parameters params;
    state s;

    init_params(&params);
    init_state(&s, &params);

    for (int i = 0; i < params.time_steps; i++) {
        step(&s, &params, 1);
    }

    print_counts(&params, &s);
    free_state(&s);

}


int main() {
    srand(time(NULL));
    run_simulation();
    return 0;
}


