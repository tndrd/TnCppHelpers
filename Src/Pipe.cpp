#include "Pipe.hpp"

using namespace TnHelpers;
using namespace IPC;

Pipe::Pipe(int flags) {
  int newPipeFd[2];
  int ret = pipe2(newPipeFd, flags);

  if (ret < 0) THROW_ERRNO("pipe()");

  In = newPipeFd[1];
  Out = newPipeFd[0];
}

int Pipe::ReadFd() const { return In.Get(); }
int Pipe::WriteFd() const { return Out.Get(); }