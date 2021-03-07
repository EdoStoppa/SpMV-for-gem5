#include <chrono>
#include <iostream>
#include <vector>

#include "options.hpp"
#include "utils.hpp"
#include "FileToVT.hpp"
#include "Triplet.hpp"
#include "ULIdef.hpp"
#include "CRS.hpp"
#include "TS.hpp"

using clock_type = std::chrono::high_resolution_clock;

//////////////////////////////////////////////////
//////////////////////////////////////////////////

int main(int argc, char *argv[]) {

    srand(12);
    std::cout << "SpMV" << std::endl;
    
    // Obtain arguments
    Options options(argc, argv);
    int num_iter = options.num_iter;
    std::string dataset = "./data/" + options.dataset;
    bool verbose = options.verbose;

    // Read dataset and transform it in Triplet format
    ULI m;
    ULI n;
    unsigned long int nnz;
    std::vector<Triplet<double>> tripVec = FileToVT::parse(dataset, m, n, nnz);

    // Create all variables necessary
    std::vector<long> times1(num_iter);
    std::vector<long> times2(num_iter);
    std::vector<double> res1(m, 0);
    std::vector<double> res2(m, 0);
    std::vector<double> vec(n);
    initialize_random_array(vec);

    // Generate the CSR an COO compressions
    CRS<double> crs(tripVec, m, n, 0.0);
    TS<double> coo(tripVec, m, n, 0.0);

    for(int i=0; i<num_iter; i++){
        // Perform CSR and record it's time
        auto start = clock_type::now();
        crs.zax(vec.data(), res1.data());
        auto end = clock_type::now();
        times1[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Perform COO and record it's time
        start = clock_type::now();
        coo.zax(vec.data(), res2.data());
        end = clock_type::now();
        times2[i] = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Reset result vectors
        res1 = std::vector<double>(m,0);
        res2 = std::vector<double>(m,0);
    }

    if(verbose){
        int old_precision = std::cout.precision();
        std::cout.precision(2);
        std::cout << "----------------" << std::endl;
        std::cout << "Dataset: " << options.dataset << std::endl;
        std::cout << "CSR mean execution time=" << mean<long, float>(times1.data(), times1.size()) / 1000 << "±" << st_dev<long, float>(times1.data(), times1.size()) / 1000 << " ms" << std::endl;
        std::cout << "COO mean execution time=" << mean<long, float>(times2.data(), times2.size()) / 1000 << "±" << st_dev<long, float>(times2.data(), times2.size()) / 1000 << " ms" << std::endl;
        std::cout << "----------------" << std::endl;
        std::cout.precision(old_precision);
    }
}