#include <iostream>
#include <cmath>
#include <chrono>       // measure time

/**
 * @brief Uniform random number generator
 * 
 * @param low 
 * @param hi 
 * @return float 
 */
float random_data(float low, float hi) {

   float r = (float)rand() / (float)RAND_MAX;

   return low + r * (hi - low);

}

/**
 * @brief Approximate π via naïve Monte Carlo simulation on the unit square 
 * 
 * @param n 
 * @return float 
 */
float pi_estimate(long n) {
    float x1, x2;
    long m = 0;
    for (int i=0; i < n; i++) {
        x1 = random_data(0.0, 1.0);
        x2 = random_data(0.0, 1.0);

        if(x1*x1 + x2*x2 <= 1.0) {
            ++m;
        }
    }

    return (4.0*m) / n; 
}

int main() {

    // Calculate the value of $\pi$ using information above, for N = 100, 1000 and 10000. Write the results to the standard output.

    // N = 100, 1000 and 10000.

     // stop the time
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    // do
    for (int n_loc = 100; n_loc <= 10000; n_loc = n_loc*10){
        std::cout << "Pi estimate (N=" << n_loc << "): \t" << pi_estimate(n_loc) << std::endl;
    }

    // stop time 
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    // print time 
    std::cout << "\nElapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms\n";


    return 0;
}