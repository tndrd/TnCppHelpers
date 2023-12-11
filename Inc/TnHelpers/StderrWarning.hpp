#pragma once

#include <iostream>
#include <string>
#include <string.h>

#include "Macro.hpp"

using std::string_literals::operator""s;

#define STDERR_WARN(msg) std::cerr << LOC_STAMP << "Warning: " << msg << std::endl
#define STDERR_WARN_CUSTOM_ERRNO(msg, err) STDERR_WARN(msg + ": "s + strerror(err))
#define STDERR_WARN_ERRNO(msg) STDERR_WARN_CUSTOM_ERRNO(msg, errno)

