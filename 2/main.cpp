
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <set>

#include "aoc.hpp"

#define TEST_INPUT_1_FILENAME "./test1.txt"
#define TEST_INPUT_2_FILENAME "./test2.txt"
#define INPUT_FILENAME "./input.txt"

uint64_t part_one(struct input_arr);
uint64_t part_two(struct input_arr);

void run_test(const char* filename) {
    clock_t test_begin = clock();
    printf("==============================\n");
    printf("Running test file \"%s\"\n", filename);
    
    clock_t begin = clock();
    struct input_arr input = read_inputfile(filename);
    clock_t end = clock();
    print_input(input);
    double input_parse_time = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("\tParsed input in  %.6fs\n", input_parse_time);

    begin = clock();
    uint64_t part_one_answer = part_one(input);
    end = clock();
    double part_one_time = (double)(end - begin) / CLOCKS_PER_SEC;

    begin = clock();
    uint64_t part_two_answer = part_two(input);
    end = clock();
    double part_two_time = (double)(end - begin) / CLOCKS_PER_SEC;

    printf("\tPart One Answer (%.6fs):\t%lu\n", part_one_time, part_one_answer);
    printf("\tPart Two Answer (%.6fs):\t%lu\n", part_two_time, part_two_answer);

    free_input(input);

    clock_t test_end = clock();
    double test_time = (double)(test_end - test_begin) / CLOCKS_PER_SEC;
    printf("Ran entire test in %.6fs\n", test_time);
    printf("==============================\n");
}

int main(int argc, char** argv) {
    run_test(TEST_INPUT_1_FILENAME);
    //run_test(TEST_INPUT_2_FILENAME); 
    run_test(INPUT_FILENAME);
    exit(EXIT_SUCCESS);
}

uint64_t part_one(struct input_arr input) {
    int forward = 0;
    int depth = 0;
    for(auto step: input.vec) {
        switch(step.dir) {
            case FWD: {
                forward += step.val;
            } break;
            case DWN: {
                depth += step.val;
            } break;
            case UP: {
                depth -= step.val;
            } break;
            default: {

            } break;
        }
    }
    return forward * depth;
    return 0;
}

uint64_t part_two(struct input_arr input) {
    int aim = 0;
    int forward = 0;
    int depth = 0;
    for(auto step: input.vec) {
        switch(step.dir) {
            case FWD: {
                forward += step.val;
                depth += (aim * step.val);
            } break;
            case DWN: {
                aim += step.val;
            } break;
            case UP: {
                aim -= step.val;
            } break;
            default: {

            } break;
        }
    }
    return forward * depth;
    return 0; 
}