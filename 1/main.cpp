
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
    std::vector<int> diffs;
    int increases = 0;
    for(int i = 0; i < input.vec.size() - 1; i++) {
        int diff = input.vec[i+1].depth - input.vec[i].depth;
        increases += (diff > 0 ? 1 : 0);
        diffs.push_back(input.vec[i+1].depth - input.vec[i].depth);
    }
    return increases;
    return 0;
}

uint64_t part_two(struct input_arr input) {
    int sum = 0;
    int prev_sum = 0;
    int increases = 0;

    prev_sum = input.vec[0].depth + input.vec[1].depth + input.vec[2].depth;
    for(int i = 1; i < input.vec.size() - 2; i++) {
        sum = input.vec[i].depth + input.vec[i+1].depth + input.vec[i+2].depth;
        if(sum > prev_sum) increases++;
        prev_sum = sum;
    }
    return increases;
    return 0; 
}