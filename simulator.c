//
// Created by fayd on 6/11/20.
//

#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"

void init_state(state* state, parameters* params) {

    state->time_step = 0;
    state->population = malloc(sizeof(person) * params->pop_size);

    for (int i = 0; i < params->pop_size; i++) {
        state->population[i] = (person) {
                .infected = 0,
                .infected_time = 0,
                .diagnosed = 0,
                .has_been_infected = 0,
                .has_infected = 0,
                .deceased = 0
        };
    }

    for (int i = 0; i < params->infected0; i++) {
        state->population[i].infected = 1;
        state->population[i].has_been_infected = 1;
    }

    state->s_counts = malloc(sizeof(int) * params->time_steps);
    state->i_counts = malloc(sizeof(int) * params->time_steps);
    state->r_counts = malloc(sizeof(int) * params->time_steps);
    state->d_counts = malloc(sizeof(int) * params->time_steps);

}


double rnd() {
    return (double) rand() / (double) RAND_MAX;
}

void step(state* s, parameters* params, int verbose) {

    if (verbose) printf("Time Step: %d\n", s->time_step);


    person* infected[params->pop_size];
    person* susceptible[params->pop_size];
    int infected_count = 0;
    int susceptible_count = 0;
    int deceased_count = 0;
    for (int i = 0; i < params->pop_size; i++) {
        person* p = &s->population[i];
        if (p->deceased) deceased_count++;
        else if (p->infected) infected[infected_count++] = p;
        else susceptible[susceptible_count++] = p;
    }

    double prob_of_infection = (params->r0 / (double) params->recover_time);
    const int current_infected_count = infected_count;
    for (int i = 0; i < current_infected_count; i++) {

        person* infected_person = infected[i];
        if (infected_person->has_infected < params->r0) {

            // Infect new people
            if (rnd() < prob_of_infection) {
                person* new_infected_person = susceptible[--susceptible_count];
                new_infected_person->infected = 1;
                new_infected_person->has_been_infected = 1;
                infected_person->has_infected++;
                infected_count++;
                // printf("Someone was infected.\n");

                // No susceptible people left
                if (susceptible_count == 0)
                    break;
            }
        }

    }



    for (int i = 0; i < params->pop_size; i++) {
        person* p = &s->population[i];
        if (p->deceased) continue;

        // Update infection times
        if (p->infected) {
            p->infected_time++;

            if (rnd() < params->death_rate) {
                p->deceased = 1;
                deceased_count++;
                infected_count--;
            }

            // Recover if person has been infected for long enough
            else if (p->infected_time >= params->recover_time) {
                p->infected = 0;
                p->infected_time = 0;
            }


        }

    }

    int recovered_count = 0;
    for (int i = 0; i < params->pop_size; i++) {
        person* p = &s->population[i];
        if (p->has_been_infected && !p->infected && !p->deceased) recovered_count++;
    }


    s->s_counts[s->time_step] = susceptible_count;
    s->i_counts[s->time_step] = infected_count;
    s->r_counts[s->time_step] = recovered_count;
    s->d_counts[s->time_step] = deceased_count;

    if (verbose) {
        printf("Recovered Count: %d\n", recovered_count);
        printf("Susceptible Count: %d\n", susceptible_count);
        printf("Infected Count: %d\n", infected_count);
        printf("Deceased Count: %d\n\n", deceased_count);
    }

    s->time_step++;

}
