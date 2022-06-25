#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>    // std::sort
#include <chrono>       // measure time
#include <cmath>        // round 
#include "load.h"

#define MAX_OUTPUT 100

struct myclass {
  bool operator() (int i,int j) { return (i<j);}
} myobject;

/**
 * Bubble Sort of list/array of integers.
 *
 * @param numbers IntVector of numbers
 */
void bubble_sort(IntVector& numbers){

  int n = numbers.size();
  int tmp; 

  for (int i=0; i < n; i++){
    for (int j=0; j < n-i; j++){
      if(numbers[j] > numbers[j+1]){
        tmp = numbers[j+1];
        numbers[j+1] =  numbers[j];
        numbers[j] = tmp;
      }
    }
  }
}

/**
 * @brief Get pivot element for quicksort 
 * 
 */
int partition(IntVector& numbers, int i, int j){
  int pivot, l, tmp;
  pivot = numbers[j];

  // temporary pivot
  l = i - 1;

  // loop
  for(int k=0; k < j-1; k++){
    // pivot if current element is less or equal to pivot
    if (numbers[k] <= pivot) {
      l++; 

      //swap current element
      tmp = numbers[l];
      numbers[l] = numbers[k];
      numbers[k] = tmp; 
    }
  }

  // move pivot to correct position
  l++; 

  tmp = numbers[l];
  numbers[l] = numbers[j];
  numbers[j] = tmp; 

  return l;
}


/**
 * Quick Sort of list/array of integers with Hoare's Partition.
 *
 * @param numbers IntVector of numbers
 */
void quick_sort(IntVector& numbers, int i = -1, int j = -1){

  int n = numbers.size();
  if (i==-1){
    i = 0;
    j = n-1;
  }

  if(i < j && i >= 0) {
    int p = partition(numbers, i, j);
    quick_sort(numbers, i, p-1);
    quick_sort(numbers, p+1, j);
  }
}

int main() {

  std::string filename = "/Users/carlo/VS_Projects/Cpp_Dump/Cpp_Testbed/Sorting/data/seq.csv";
  IntVector numbers;

  // check file existence
  std::cout << file_exists(filename) << std::endl;

  ReadNumbers(filename, '\n', numbers); /// test

  // Output the numbers
  std::cout << "Numbers read:\n";
  for (int i=0; i < numbers.size() && i < MAX_OUTPUT; i++) {
    std::cout << numbers[i] << ", ";
  }
  std::cout << "\n...\n";

  // convert numbers properly
  std::vector<int> numbers_vec(numbers.size(), 0);
  for (int i=0; i < numbers.size() && i < MAX_OUTPUT; i++) {
      numbers_vec[i] = (int)numbers[i];
  }


  // stop the time
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();

  // gold standard of sorting: std::sort()
  //std::sort (numbers_vec.begin(), numbers_vec.end(), myobject);
  quick_sort(numbers);

  // stop time 
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

  // print time 
  std::cout << "\nElapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms\n";


  // Output the numbers
  std::cout << "\nNumbers read:\n";
  for (int i=0; i < numbers_vec.size() && i < MAX_OUTPUT; i++) {
    std::cout << numbers_vec[i] << ", ";
  }
  std::cout << "\n- - - - - - - - - - - - - - - - - -" << std::endl;


  return 0;
}