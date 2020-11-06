#include <stdio.h>

#include "simulator.h"

void run_simulation(parameters* params) {

    for (int i = 0; i < params->time_steps; i++) {

        printf("Time Step: %d\n", i);

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


