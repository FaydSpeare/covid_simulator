    #include <time.h>
    #include <stdio.h>
    #include <stdlib.h>

    #include "simulator.h"

    const int TIME_STEPS = 1000;

    void print_array_int(int* array, int len) {
        printf("[");
        for (int i = 0; i < len; i++) {
            printf("%d ", array[i]);
        }
        printf("]\n");
    }

    void print_array_double(double* array, int len) {
        printf("[");
        for (int i = 0; i < len; i++) {
            printf("%f ", array[i]);
        }
        printf("]\n");
    }

    void print_counts(parameters* params, state* s) {
        print_array_int(s->susceptible_counts, params->time_steps);
        print_array_int(s->infected_counts, params->time_steps);
        print_array_int(s->deceased_counts, params->time_steps);
        print_array_int(s->recovered_counts, params->time_steps);
        print_array_int(s->diagnosed_counts, params->time_steps);
    }

    void init_params(parameters* params) {
        params->pop_size = 100;
        params->time_steps = TIME_STEPS;
        params->r0 = 4.11;
        params->r0_diagnosed = 0.0;
        params->death_rate = 0.001;
        params->recover_time = 10;
        params->infected0 = 5;
        params->test_rate = 0.3;
    }

    void run_simulation(state* s, parameters* params, int verbose) {

        init_params(params);
        init_state(s, params);

        for (int i = 0; i < params->time_steps; i++) {
            step(s, params, verbose);
        }

        if (verbose) print_counts(params, s);

    }

    void run_n_simulations(int n, int verbose) {

        double susceptible_count[TIME_STEPS];
        double infected_count[TIME_STEPS];
        double deceased_count[TIME_STEPS];
        double diagnosed_count[TIME_STEPS];

        for (int i = 0; i < TIME_STEPS; i++) {
            susceptible_count[i] = 0.;
            infected_count[i] = 0.;
            deceased_count[i] = 0.;
        }

        for (int i = 0; i < n; i++) {

            parameters params;
            state s;
            run_simulation(&s, &params, verbose);

            for (int j = 0; j < TIME_STEPS; j++) {
                susceptible_count[j] += s.susceptible_counts[j];
                infected_count[j] += s.infected_counts[j];
                deceased_count[j] += s.deceased_counts[j];
                diagnosed_count[j] += s.diagnosed_counts[j];
            }
            free_state(&s);
        }

        for (int i = 0; i < TIME_STEPS; i++) {
            susceptible_count[i] /= (double) n;
            infected_count[i] /= (double) n;
            deceased_count[i] /= (double) n;
        }

        print_array_double(susceptible_count, TIME_STEPS);
        print_array_double(infected_count, TIME_STEPS);
        print_array_double(deceased_count, TIME_STEPS);
        print_array_double(diagnosed_count, TIME_STEPS);
    }


    int main() {
        srand(time(NULL));
        run_n_simulations(100, 0);
        return 0;
    }


