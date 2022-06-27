#include <iostream>
#include <cmath>
#include <string>
#include <chrono>       // measure time
#include <Eigen/Dense>
#include "load.h"

int main() {

    // load data: x1_mini.csv, x2_mini.csv, y_mini.csv 
    std::string filepath = "/Users/carlo/VS_Projects/Cpp_Dump/Cpp_Testbed-1/Machine_Learning/data/.csv";
    std::string filepath1 = filepath;
    std::string filepath2 = filepath;
    std::string filepath3 = filepath;

    std::string file_1 = "x1_mini";
    std::string file_2 = "x2_mini";
    std::string file_3 = "y_mini";

    filepath1.insert(70, file_1);
    filepath2.insert(70, file_2);
    filepath3.insert(70, file_3);

    // declare 
    FlVector x1, x2, y;

    // check file existence
    std::cout << file_exists(filepath1) << std::endl;

    ReadNumbers(filepath1, '\n', x1); /// test
    ReadNumbers(filepath2, '\n', x2); /// test
    ReadNumbers(filepath3, '\n', y); /// test

    Eigen::MatrixXd X(x1.size(),3);
    Eigen::MatrixXd Y(y.size(),1);

    for (int i=0; i < x1.size(); i++) {
        X(i,0) = 1.0; // intercept (obligatory!)
        X(i,1) = x1[i];
        X(i,2) = x2[i];
        Y(i,0) = y[i];
    }

    // OLS estimator (X.T * X)^{-1} * X.T*y

    Eigen::MatrixXd beta_hat = (X.transpose() * X).inverse() * X.transpose() * Y;

    std::cout << "Finally running: " << std::endl;

    std::cout << beta_hat;


    return 0;
}