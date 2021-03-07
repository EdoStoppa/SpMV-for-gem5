#pragma once

#include <getopt.h>
#include <cstdlib>

//////////////////////////////
//////////////////////////////

#define NUM_ITER 1
#define DEFAULT_DATASET "test.mtx"
#define VERBOSE false

//////////////////////////////
//////////////////////////////

struct Options {
    // Testing options;
    uint num_iter = NUM_ITER;
    std::string dataset = DEFAULT_DATASET;
    bool verbose = VERBOSE;

    //////////////////////////////
    //////////////////////////////

    Options(int argc, char *argv[]) {

        int opt;
        static struct option long_options[] = {{"num_iter", required_argument, 0, 'i'},
                                               {"dataset", required_argument, 0, 'd'},
                                               {"verbose", no_argument, 0, 'v'},
                                               {0, 0, 0, 0}};
        // getopt_long stores the option index here;
        int option_index = 0;

        while ((opt = getopt_long(argc, argv, "i:d:v", long_options, &option_index)) != EOF) {
            switch (opt) {
                case 'i':
                    num_iter = atoi(optarg);
                    break;
                case 'd':
                    dataset = optarg;
                    break;
                case 'v':
                    verbose = true;
                    break;
                default:
                    break;
            }
        }
    }
};