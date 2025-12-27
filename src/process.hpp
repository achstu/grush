#pragma once

#include <string>

class ChildProcess {
private:
  int pid;
  int stdin_pipe[2];
  int stdout_pipe[2];

public:
  ChildProcess(const std::string &command);
  ~ChildProcess();

  void write(const std::string &message);
  std::string readline();
  char getchar();
};
