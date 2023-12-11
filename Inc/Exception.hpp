#pragma once
#include <string.h>
#include <errno.h>

#include <stdexcept>
#include <string>

#include "Macro.hpp"

namespace TnHelpers {

using std::string_literals::operator""s;

class Exception : public std::exception {
 private:
  std::string Message;
  const char* File;
  const char* Function;
  const char* Line;

  mutable std::string Buf;

 public:
  Exception(const std::string& message, const char* file, const char* function,
            const char* line);

  virtual const char* what() const noexcept override;
  virtual ~Exception() = default;
};

#define THROW(msg) \
  throw TnHelpers::Exception(msg, __FILE__, __FUNCTION__, XSTRINGIFY(__LINE__))

#define THROW_CUSTOM_ERRNO(msg, err) THROW(msg + ": "s + strerror(err))
#define THROW_ERRNO(msg) THROW_CUSTOM_ERRNO(msg, errno)

}  // namespace TnHelpers