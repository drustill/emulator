class Logger
{
  const char* filepath;

  public:
    Logger(const char* file) : filepath(file) {}

    void log(const char* msg);
};
