#pragma once

#include <fstream>
#include <iostream>

class Logger
{
  public:
    Logger(const char* file = "_log.txt") { fs.open(file, std::fstream::in | std::fstream::out | std::fstream::trunc); }

    std::fstream fs;

    void log(const char* msg, ...);
};

extern Logger _logger;

#define LOG(...) _logger.log(__VA_ARGS__);
#define CLOSE() _logger.fs.close();
