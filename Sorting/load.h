#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream> 
#include <fstream>
#include <string>
#include <vector>

typedef std::vector<std::string> StringVector;
typedef std::vector<int> IntVector;

void ReadNumbers(const std::string& filename, char sep, IntVector& output);
bool file_exists(const std::string& name);


#endif