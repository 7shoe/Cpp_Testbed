#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include "load.h"

int main() {

  std::string filename = "/Users/carlo/VS_Projects/Cpp_Dump/Cpp_Testbed/Sorting/data/seq_mini.csv";
  IntVector numbers;

  // check file existence
  //std::cout << file_exists(filename) << std::endl;

  ReadNumbers(filename, '\n', numbers);

  // Output the numbers
  //std::cout << "Numbers read:\n";
  //for (int i=0; i < numbers.size(); i++)
  //  std::cout << numbers[i] << '\t';
  //std::cout << "\n\n";

  //system("pause");

  return 0;
}