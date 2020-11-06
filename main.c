#include <stdlib.h>
#include <stdio.h>

#include "simulator.h"

void print_array(int* arrray, int len) {
    printf("[");
    for (int i = 0; i < len; i++) {
        printf("%d ", arrray[i]);
    }
    printf("]\n");
}

void print_counts(parameters* params, state* s) {
    print_array(s->s_counts, params->time_steps);
    print_array(s->i_counts, params->time_steps);
    print_array(s->d_counts, params->time_steps);
    print_array(s->r_counts, params->time_steps);
}

void init_params(parameters* params) {
    params->pop_size = 100;
    params->time_steps = 50;
    params->r0 = 2.11;
    params->death_rate = 0.001;
    params->recover_time = 10;
    params->infected0 = 1;
    params->test_rate = 0.1;
}

void run_simulation() {

    parameters params;
    state s;

    init_params(&params);
    init_state(&s, &params);

    for (int i = 0; i < params.time_steps; i++) {
        step(&s, &params, 0);
    }

    print_counts(&params, &s);

}


int main() {
    run_simulation();
    return 0;
}


