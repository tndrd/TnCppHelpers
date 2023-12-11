#pragma once

#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include "Exception.hpp"
#include "FileDescriptor.hpp"
#include "UniqueValue.hpp"

namespace TnHelpers {
namespace IPC {

class Pipe {
 private:
  FileDescriptor In;
  FileDescriptor Out;

 public:
  Pipe(int flags = 0);

  Pipe(Pipe&& rhs) = default;
  Pipe& operator=(Pipe&& rhs) = default;
  ~Pipe() = default;

  int ReadFd() const;
  int WriteFd() const;
};

}  // namespace IPC
}  // namespace TnHelpers