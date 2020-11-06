cmake_minimum_required(VERSION 3.17)
project(covid_simulator C)

set(CMAKE_C_STANDARD 99)

add_executable(covid_simulator main.c simulator.c simulator.h)