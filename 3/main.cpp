
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <set>
#include <math.h>

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
    // Strategy will be accumulate set bits at each position
    // We can then divide by number of inputs to get "average" bit, and
    // round up to get most common, round down to get least common, etc.

    // Could also likely just invert gamma rate to get epsilon rate, but part
    // two might need more flexibility than that.
    std::vector<int> accums;
    for(int i = 0; i < input.vec[0].bitlength; i++) {
        accums.push_back(0);
    }

    // NOTE: assume all items have the same number of bits
    for(auto item: input.vec) {
        for(int i = 0; i < item.bitlength; i++){
            uint64_t this_bit = item.num & (1 << i);
            accums[i] += (this_bit > 0) ? 1 : 0;
        }
    }

    uint64_t gamma_rate = 0;
    uint64_t eps_rate = 0;
    for(int i = 0; i < input.vec[0].bitlength; i++) {
        float average_bit = (float)accums[i] / input.vec.size();
        uint64_t new_bit = lroundf(average_bit) << i;
        uint64_t new_inv_bit = lroundf(1-average_bit) << i;
        gamma_rate |= new_bit;
        eps_rate |= new_inv_bit;
    }
    return gamma_rate * eps_rate;
    return 0;
}

uint64_t most_common_bit(std::vector<uint64_t> vec, int bitpos, uint64_t def) {
    int accum = 0;
    for(auto item: vec) {
        char bit = (item & (1 << bitpos)) > 0 ? 1 : 0;
        accum += bit;
    }
    float average = (float)accum / vec.size();
    uint64_t bitval;

    // If there's a tie, go with whatever default we specify
    if (average == 0.5f) {
        bitval = def;
    }

    else {
        bitval = lroundf(average);
    }

    return bitval << bitpos;
}

std::vector<uint64_t> filter_by_most_common(std::vector<uint64_t> vec, int bitpos) {
    std::vector<uint64_t> retvec;

    uint64_t target_bit = most_common_bit(vec, bitpos, (uint64_t)1);
    for(auto item: vec) {
        uint64_t itembit = item & (1 << bitpos);
        if(itembit == target_bit)
            retvec.push_back(item);
    }
    return retvec;
}

std::vector<uint64_t> filter_by_least_common(std::vector<uint64_t> vec, int bitpos) {
    std::vector<uint64_t> retvec;

    uint64_t target_bit = most_common_bit(vec, bitpos, (uint64_t)1);

    // Invert the target bit to find least common bit
    target_bit = target_bit ^ (1 << bitpos);

    for(auto item: vec) {
        uint64_t itembit = item & (1 << bitpos);
        if(itembit == target_bit)
            retvec.push_back(item);
    }
    return retvec;
}

uint64_t part_two(struct input_arr input) {
    int bitlength = input.vec[0].bitlength;

    // Convert input.vec into vec of uint64_t's for ease of use
    std::vector<uint64_t> items = {};
    for(auto item: input.vec) {
        items.push_back(item.num);
    }

    // NOTE: lots of deep copies of vectors floating around here, which isn't
    //   ideal. Could have front and back vector ptrs that get cleared if
    //   copying became bottleneck for some reason. 
    std::vector<uint64_t> curvec = items;
    for(int i = bitlength - 1; i >= 0; i--) {
        curvec = filter_by_most_common(curvec, i);
        if(curvec.size() == 1) break;
    }
    uint64_t o2rating = curvec[0];

    curvec = items;
    for(int i = bitlength - 1; i >= 0; i--) {
        curvec = filter_by_least_common(curvec, i);
        if(curvec.size() == 1) break;
    }
    uint64_t co2rating = curvec[0];

    return o2rating * co2rating;
    return 0; 
}