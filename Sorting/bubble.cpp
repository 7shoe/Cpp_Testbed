#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include "load.h"


void naive_sort(IntVector& numbers){

  int n = numbers.size();
  int tmp; 
  bool isSorted_flag = false; 

  while (!isSorted_flag) {
    for (int j = 0; j < n-1; ++j ){
      if (numbers[j] > numbers[j+1]){
        tmp = numbers[j+1];
        numbers[j+1] =  numbers[j];
        numbers[j] = tmp;
      } else {
        break; 
      }
    }
    isSorted_flag = true; 
  }
}

int main() {

  std::string filename = "/Users/carlo/VS_Projects/Cpp_Dump/Cpp_Testbed/Sorting/data/seq_mini.csv";
  IntVector numbers;

  // check file existence
  std::cout << file_exists(filename) << std::endl;

  ReadNumbers(filename, '\n', numbers); /// test

  // Output the numbers
  std::cout << "Numbers read:\n";
  for (int i=0; i < numbers.size(); i++) {
    std::cout << numbers[i] << ", ";
  }
  std::cout << "\n...\n";

  // sort
  naive_sort(numbers);

  // Output the numbers
  std::cout << "Numbers read:\n";
  for (int i=0; i < numbers.size(); i++) {
    std::cout << numbers[i] << ", ";
  }


  return 0;
}