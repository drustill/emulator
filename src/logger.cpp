#include "logger.h"

// https://en.cppreference.com/w/c/variadic/va_start

Logger _logger;

void Logger::log(const char* msg, ...)
{

  va_list args;
  va_start(args, msg);

  std::string formatted_msg = std::string(msg);
  va_end(args);

  fs << formatted_msg << std::endl;
}
