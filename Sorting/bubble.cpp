#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>    // std::sort
#include <chrono>       // measure time
#include <cmath>        // round 
#include "load.h"

#define MAX_OUTPUT 20

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
  int x = numbers[j];
  int l = i-1;
  int tmp; 

  // temporary pivot
  for (int k=i; k < j; k++) {
    if (numbers[k] <= x) {
      l++;
      // swap
      tmp = numbers[l];
      numbers[l] = numbers[k];
      numbers[k] = tmp;
    }
  }

  // swap
  tmp = numbers[l+1];
  numbers[l+1] = numbers[j];
  numbers[j] = tmp;

  return l+1;
}


/**
 * Quick Sort of list/array of integers with Hoare's Partition.
 *
 * @param numbers IntVector of numbers
 */
void quicksort(IntVector& numbers, int i, int j){

  if(i < j) {
    int p = partition(numbers, i, j);
    quicksort(numbers, i, p-1);
    quicksort(numbers, p+1, j);
  }
}


/**
 * Merge Sort of list/array of integers
 *
 * @param numbers IntVector of numbers
 */
void mergesort(IntVector& numbers, int i, int j){
  ;
}

/**
 *merge two sub-list/sub-array of integers
 *
 * @param numbers IntVector of numbers
 */
void merge(IntVector& numbers, int i, int j){
  ;
}

/**
 *split into two sub-list/sub-array of integers
 *
 * @param numbers IntVector of numbers
 */
void split(IntVector& numbers, int i, int j){
  ;
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
  quicksort(numbers, 0, numbers.size());

  // stop time 
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

  // print time 
  std::cout << "\nElapsed time: " << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() << " ms\n";


  // Output the numbers
  std::cout << "\nNumbers read:\n";
  for (int i=0; i < numbers.size() && i < MAX_OUTPUT; i++) {
    std::cout << numbers[i] << ", ";
  }
  std::cout << "\n- - - - - - - - - - - - - - - - - -" << std::endl;


  return 0;
}