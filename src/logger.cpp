#include "logger.h"

// https://en.cppreference.com/w/c/variadic/va_start

Logger _logger;

void Logger::log(const char* msg, ...)
{

  va_list args;
  va_start(args, msg);

  std::string formatted_msg = fmt(msg, args);
  va_end(args);

  fs << formatted_msg << std::endl;
}

std::string Logger::fmt(const char* msg, va_list args)
{
  char buffer[256];

  // https://cplusplus.com/reference/cstdio/vsnprintf/

  vsnprintf(buffer, sizeof(buffer), msg, args);
  return std::string(buffer);
}
