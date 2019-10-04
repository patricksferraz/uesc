cmake_minimum_required(VERSION 3.10)
project(projeto_1 C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -fopenmp -lm")

add_executable(projeto_1 main.c functionsix.c functionsix.h functionsix_processor.c functionsix_processor.h output_generator.c output_generator.h)