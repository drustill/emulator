#include <fstream>
#include <iostream>

#include "logger.h"

void Logger::log(const char* msg)
{
  std::fstream fs;
  fs.open(filepath, std::fstream::in | std::fstream::out | std::fstream::app);

  fs << msg << "\n";

  fs.close();
}
