#include "process.hpp"
#include <stdexcept>
#include <string>
#include <sys/types.h>
#include <unistd.h>
#include <cassert>
#include <sys/wait.h>

ChildProcess::ChildProcess(const std::string& command) {

  if (pipe(stdin_pipe) == -1 || pipe(stdout_pipe) == -1) {
    throw std::runtime_error("Pipe failed");
  }
  
  pid = fork();
  if (pid == 0) {
    // child process
    dup2(stdin_pipe[0], STDIN_FILENO);
    dup2(stdout_pipe[1], STDOUT_FILENO);

    close(stdin_pipe[0]);
    close(stdin_pipe[1]);
    close(stdout_pipe[0]);
    close(stdout_pipe[1]);

    execlp("sh", "sh", "-c", command.c_str(), nullptr);
    exit(1);
  } else if (pid > 0) {
    // parent process
    close(stdin_pipe[0]);
    close(stdout_pipe[1]);
  } else {
    throw std::runtime_error("Fork failed");
  }
}

ChildProcess::~ChildProcess() {
  if (pid > 0) {
    close(stdin_pipe[1]);
    close(stdout_pipe[0]);
    waitpid(pid, nullptr, 0);
  }
}

void ChildProcess::write(const std::string& message) {
  ::write(stdin_pipe[1], message.c_str(), message.size());
  ::write(stdin_pipe[1], "\n", 1);
}

std::string ChildProcess::readline() {
  std::string line;
  char buffer[256];
  ssize_t bytes;

  while ((bytes = read(stdout_pipe[0], buffer, sizeof(buffer)-1)) > 0) {
    buffer[bytes] = '\0';
    line += buffer;
    if (line.find('\n') != std::string::npos) {
      break;
    }
  }

  if (!line.empty() && line.back() == '\n') {
    line.pop_back();
  }

  return line;
}
