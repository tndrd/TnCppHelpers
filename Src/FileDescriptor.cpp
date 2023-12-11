#include "FileDescriptor.hpp"

using namespace TnHelpers;

FileDescriptor::FileDescriptor(int fd)
    : UniqueValue{std::move(fd)} {}

FileDescriptor::FileDescriptor(): UniqueValue{-1} {}

FileDescriptor::~FileDescriptor() {
  if (Get() < 0) return;

  int ret = close(Get());
  if (ret < 0) STDERR_WARN_ERRNO("close()");
}