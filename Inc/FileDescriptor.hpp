#pragma once
#include <string.h>
#include <unistd.h>

#include <iostream>
#include <string>
#include <utility>

#include "UniqueValue.hpp"
#include "StderrWarning.hpp"

namespace TnHelpers {

class FileDescriptor final: public UniqueValue<int> {
 public:
  FileDescriptor(int);
  FileDescriptor();
  ~FileDescriptor();

  FileDescriptor(FileDescriptor&&) = default;
  FileDescriptor& operator=(FileDescriptor&&) = default;
};

}  // namespace HwBackup