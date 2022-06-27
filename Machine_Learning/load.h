#ifndef FUNCTIONS_H_INCLUDED
#define FUNCTIONS_H_INCLUDED

#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include "load.h"

typedef std::vector<std::string> StringVector;
typedef std::vector<float> FlVector;

void ReadNumbers(const std::string& filename, char sep, FlVector& output){
  std::ifstream src(filename);

  if (!src)
  {
    std::cerr << "\aError opening file.\n\n";
    exit(EXIT_FAILURE);
  }
  std::string buffer;
  size_t strpos = 0;
  size_t endpos;
  while(std::getline(src, buffer))
  {
    endpos= buffer.find(sep); 
    while (endpos < buffer.length())
    {  
      output.push_back(std::stof(buffer.substr(strpos,endpos - strpos)));
      strpos = endpos + 1;
      endpos = buffer.find(sep, strpos);
    }
    output.push_back(std::stof(buffer.substr(strpos)));
  }
}

bool file_exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}
#endif