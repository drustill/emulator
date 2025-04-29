#pragma once

#include <fstream>
#include <iostream>

class Logger
{
  public:
    Logger(const char* file = "_log.log") { fs.open(file, std::fstream::in | std::fstream::out | std::fstream::trunc); }

    std::fstream fs;

    std::string fmt(const char* msg, va_list args);
    void log(const char* msg, ...);
};

extern Logger _logger;

#define LOG(...) _logger.log(__VA_ARGS__);
#define CLOSE() _logger.fs.close();
