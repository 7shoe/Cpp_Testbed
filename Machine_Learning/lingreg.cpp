#include <iostream>
#include <cmath>
#include <string>
#include <chrono>       // measure time
#include <Eigen/Dense>
#include <boost/math/distributions/students_t.hpp> 
#include <boost/math/distributions/normal.hpp>
#include "load.h"

class LinearModel {
    private:
        Eigen::MatrixXf X;
        Eigen::MatrixXf Y;
        Eigen::MatrixXf beta_hat;
        Eigen::MatrixXf std_err;
        Eigen::MatrixXf Y_hat;
        Eigen::MatrixXf residuals;
        Eigen::MatrixXf t_values;
        Eigen::MatrixXf p_values;
        bool estimated_flag;
        float sigma_hat; 
        int n; 

    public:
        // Constructor
        LinearModel() : n(0) { }

        int get_n(){
            return n;
        }

        float minResidual(){
            // use vector class 
            std::vector<double> vec(n);
            for(int i=0; i < residuals.rows(); i++){
                vec[i] = (double)residuals(i,0);
            }
            std::sort(vec.begin(), vec.end()); 

            return vec[0];
        }

        float maxResidual(){
            // use vector class 
            std::vector<double> vec(n);
            for(int i=0; i < residuals.rows(); i++){
                vec[i] = (double)residuals(i,0);
            }
            std::sort(vec.begin(), vec.end()); 

            return vec[n-1];
        }

        float meanResidual(){
            float meanVal = 0.0; 
            for(int i=0; i < residuals.rows(); i++){
                meanVal += residuals(i,0);
            }
            meanVal /= (1.0*n);

            return meanVal;
        }

        float quantile(float p){
            // use vector class 
            std::vector<double> vec(n);
            for(int i=0; i < residuals.rows(); i++){
                vec[i] = (double)residuals(i,0);
            }
            std::sort(vec.begin(), vec.end()); 
            int p_k = (int)std::floor(n * p);
            if(n % 2 == 0 && p==0.5){
                return 0.5*(vec[p_k-1] + vec[p_k]);
            }else if (n % 2 == 0 && p==0.25){
                return 0.75*vec[p_k] + 0.25*vec[p_k+1];
            }else if (n % 2 == 0 && p==0.75){
                return 0.25*vec[p_k-1] + 0.75*vec[p_k];
            }else{
                return vec[p_k];
            }
        }

        Eigen::MatrixXf get_std_error(){
            return std_err;
        }

        Eigen::MatrixXf get_Y(){
            return Y;
        }

        Eigen::MatrixXf get_Y_hat(){
            return Y_hat;
        }

        Eigen::MatrixXf get_beta_hat(){
            return beta_hat;
        }

        float get_sigma_hat(){
            return sigma_hat;
        }

        Eigen::MatrixXf get_residuals(){
            return residuals;
        }

        Eigen::MatrixXf get_t_values(){
            return t_values;
        }

        void set_X(const Eigen::MatrixXf& X){
            this->X = X; 
            n = X.rows();
            Eigen::MatrixXf resid(n,1);
            resid.setZero(); 
            residuals = resid;
        }

        void set_Y(const Eigen::MatrixXf& Y){
            this->Y = Y; 
        }

        void estimate_sigma(){
            sigma_hat = 0.0;
            for (int i=0; i < n; i++) {
                sigma_hat+= residuals(i,0) * residuals(i,0);
            }
            sigma_hat *= (1.0 / (1.0 * (X.rows() - X.cols()))); 
        }
        void estimate_beta(const Eigen::MatrixXf& X, const Eigen::MatrixXf& Y) {
            beta_hat = (X.transpose() * X).inverse() * X.transpose() * Y;
        }
        void estimate_Y(const Eigen::MatrixXf& X) {
            Y_hat = X * beta_hat;
        }

        void set_residuals(){
            for (int i=0; i < n; i++){
                residuals(i,0) =  Y_hat(i,0) - Y(i,0);
            }
        }

        void set_std_error(){
            Eigen::MatrixXf Sigma = sigma_hat * (X.transpose() * X).inverse();
            Eigen::MatrixXf std_err_cpy(Sigma.rows(),1);
            for(int i=0; i < Sigma.rows(); i++){
                std_err_cpy(i,0) = (double)std::sqrt(Sigma(i,i));
            }
            std_err = std_err_cpy;
        }

        void set_t_values(){
            Eigen::MatrixXf beta = this->get_beta_hat();
            Eigen::MatrixXf t_values_cpy(beta.rows(),1);
            for(int i=0; i<beta.rows(); i++){
                t_values_cpy(i,0) = beta(i,0) / this->std_err(i,0);
            }
            t_values = t_values_cpy;
        }

        void set_p_values(){
            Eigen::MatrixXf t_vals = this->get_t_values();
            Eigen::MatrixXf p_vals(t_vals.rows(), 1);

            // define student t distribution
            // boost::math::students_t_distribution<int>::students_t_distribution dist(10);
            // boost::math::distribution::students_t_distribution(df);
            // boost::math::students_t dist(n-1);

            //boost::math::normal dist(0.0, 1.0);

            //boost::math::students_t_distribution<int> nd(10);

            // boost::math::normal_distribution myNormal = boost::math::normal_distribution<>(0.0, 1.0);

            for (int i=0; i < t_vals.rows(); i++){
                p_vals(i,0) = 1.0;
                //const auto df = 10;

                // p_vals(i,0) = quantile(dist, t_vals(i,0)); 
                //q = quantile(boost::math::students_t_distribution<int> { df }, 0.95);
            }
            p_values = p_vals;
        }

        void fit(const Eigen::MatrixXf& X, const Eigen::MatrixXf& Y){
            set_X(X);
            set_Y(Y);
            estimate_beta(X, Y);
            estimate_Y(X);
            set_residuals();
            estimate_sigma(); 
            set_std_error();
            set_t_values();
            estimated_flag = true;
        }

        Eigen::MatrixXf predict(const Eigen::MatrixXf& X_test){
            Eigen::MatrixXf Y_hat_test; 
            Y_hat_test = X_test * this->get_beta_hat(); 
            return Y_hat_test;
        }


};

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

    Eigen::MatrixXf X(x1.size(),3);
    Eigen::MatrixXf Y(y.size(),1);

    for (int i=0; i < x1.size(); i++) {
        X(i,0) = 1.0; // intercept (obligatory!)
        X(i,1) = x1[i];
        X(i,2) = x2[i];
        Y(i,0) = y[i];
    }

    // OLS estimator (X.T * X)^{-1} * X.T*y

    Eigen::MatrixXf beta_hat = (X.transpose() * X).inverse() * X.transpose() * Y;

    std::cout << "Finally running: " << std::endl;

    std::cout << beta_hat;

    // Class Object 
    LinearModel lm_1 = LinearModel(); 
    
    std::cout << "\n" << std::endl;

    std::cout << lm_1.get_n() << std::endl;

    // start the time
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

    // Fit model
    lm_1.fit(X, Y);

    // stop time 
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

    // print time 
    std::cout << "\nElapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms\n";

    // check output
    std::cout << lm_1.get_sigma_hat() << std::endl;


    // quantile
    // std::cout << "Residuals: " << lm_1.get_residuals() << std::endl;

    // quantile
    std::cout << lm_1.minResidual() << std::endl;
    std::cout << lm_1.quantile(0.25) << std::endl;
    std::cout << lm_1.quantile(0.5) << std::endl;
    std::cout << lm_1.meanResidual() << std::endl;
    std::cout << lm_1.quantile(0.75) << std::endl;
    std::cout << lm_1.maxResidual() << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << lm_1.get_std_error() << std::endl;
    std::cout << "\n" << std::endl;
    std::cout << lm_1.get_t_values() << std::endl;

    return 0;
}