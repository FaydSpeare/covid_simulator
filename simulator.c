//
// Created by fayd on 6/11/20.
//

#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"

void free_state(state* s) {
    free(s->deceased_counts);
    free(s->diagnosed_counts);
    free(s->susceptible_counts);
    free(s->infected_counts);
    free(s->recovered_counts);
}

void init_state(state* s, parameters* params) {

    s->time_step = 0;
    s->population = malloc(sizeof(person) * params->pop_size);

    for (int i = 0; i < params->pop_size; i++) {
        s->population[i] = (person) {
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

    state->susceptible_counts = malloc(sizeof(int) * params->time_steps);
    state->infected_counts = malloc(sizeof(int) * params->time_steps);
    state->recovered_counts = malloc(sizeof(int) * params->time_steps);
    state->deceased_counts = malloc(sizeof(int) * params->time_steps);
    state->diagnosed_counts = malloc(sizeof(int) * params->time_steps);

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

    const int current_infected_count = infected_count;
    for (int i = 0; i < current_infected_count; i++) {

        // No susceptible people left
        if (susceptible_count == 0)
            break;

        person* infected_person = infected[i];

        double infection_rate = params->r0;
        if (infected_person->diagnosed) infection_rate = params->r0_diagnosed;
        double prob_of_infection = (infection_rate / (double) params->recover_time);

        if (infected_person->has_infected < infection_rate) {

            // Infect new people
            if (rnd() < prob_of_infection) {
                person* new_infected_person = susceptible[--susceptible_count];
                new_infected_person->infected = 1;
                new_infected_person->has_been_infected = 1;
                infected_person->has_infected++;
                infected_count++;
                //printf("Someone was infected.\n");
            }
        }

    }

    // Testing
    for (int i = 0; i < params->pop_size; i++) {
        person* p = &s->population[i];
        if (p->deceased) continue;

        if (p->infected && rnd() < params->test_rate) {
            p->diagnosed = 1;
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
                p->diagnosed = 0;
                p->has_infected = 0;
                susceptible_count++;
                infected_count--;
                //printf("Someone recovered.\n");
            }


        }

    }

    int recovered_count = 0;
    int diagnosed_count = 0;
    for (int i = 0; i < params->pop_size; i++) {
        person* p = &s->population[i];
        if (p->deceased) continue;

        if (p->has_been_infected && !p->infected) recovered_count++;
        if (p->diagnosed) diagnosed_count++;
    }


    s->susceptible_counts[s->time_step] = susceptible_count;
    s->infected_counts[s->time_step] = infected_count;
    s->recovered_counts[s->time_step] = recovered_count;
    s->deceased_counts[s->time_step] = deceased_count;
    s->diagnosed_counts[s->time_step] = diagnosed_count;

    if (verbose) {
        printf("Recovered Count: %d\n", recovered_count);
        printf("Diagnosed Count: %d\n", diagnosed_count);
        printf("Susceptible Count: %d\n", susceptible_count);
        printf("Infected Count: %d\n", infected_count);
        printf("Deceased Count: %d\n\n", deceased_count);
    }

    s->time_step++;

}
