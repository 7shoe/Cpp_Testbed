#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
#include <sys/stat.h>
#include <unistd.h>
#include <fstream>
#include "load.h"

void ReadNumbers(const std::string& filename, char sep, IntVector& output){
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
      output.push_back(std::stoi(buffer.substr(strpos,endpos - strpos)));
      strpos = endpos + 1;
      endpos = buffer.find(sep, strpos);
    }
    output.push_back(std::stoi(buffer.substr(strpos)));
  }
}

bool file_exists(const std::string& name) {
  struct stat buffer;   
  return (stat (name.c_str(), &buffer) == 0); 
}