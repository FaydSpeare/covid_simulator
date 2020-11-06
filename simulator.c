//
// Created by fayd on 6/11/20.
//

#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"

double rnd() {
    return (double) rand() / (double) RAND_MAX;
}

void step(state* s, parameters* params) {

    s->time_step++;
    printf("Time Step: %d\n", s->time_step);


    person* infected[params->pop_size];
    person* susceptible[params->pop_size];
    int infected_count = 0;
    int susceptible_count = 0;
    for (int i = 0; i < params->pop_size; i++) {
        person* p = &s->population[i];
        if (p->infected) infected[infected_count++] = p;
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
                printf("Someone was infected.\n");
            }
        }

    }



    for (int i = 0; i < params->pop_size; i++) {
        person* p = &s->population[i];

        // Update infection times
        if (p->infected) {
            p->infected_time++;

            // Recover if person has been infected for long enough
            if (p->infected_time >= params->recover_time) {
                p->infected = 0;
                p->infected_time = 0;
            }
        }

    }


    printf("Infected Count: %d\n", infected_count);
    printf("Susceptible Count: %d\n\n", susceptible_count);

}
