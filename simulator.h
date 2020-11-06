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

} parameters;

#endif //COVID_SIMULATOR_SIMULATOR_H
