//
// Created by fayd on 6/11/20.
//

#ifndef COVID_SIMULATOR_SIMULATOR_H
#define COVID_SIMULATOR_SIMULATOR_H

typedef struct Parameters {

    // size of population to simulate
    int pop_size;

    // number of time steps to perform
    int time_steps;

    // reproduction number for virus
    double r0;

    // death rate from virus
    double death_rate;

    // time steps to recover
    int recover_time;

    // initial infected
    int infected0;

    // test rate
    double test_rate;

} parameters;


typedef struct Person {

    int infected;
    int infected_time;
    int diagnosed;
    int has_been_infected;
    int has_infected;
    int deceased;

} person;


typedef struct State {

    int time_step;
    person* population;
    int* s_counts;
    int* i_counts;
    int* r_counts;
    int* d_counts;

} state;

void init_state(state* state, parameters* params);
void step(state* state, parameters* params, int verbose);

#endif //COVID_SIMULATOR_SIMULATOR_H
