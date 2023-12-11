#pragma once

#include <dirent.h>

#include <functional>
#include <memory>
#include <stack>
#include <string>

#include "Exception.hpp"
#include "StderrWarning.hpp"

namespace TnHelpers {
namespace Files {

struct Directory {
  struct Deleter {
    void operator()(DIR* dir);
  };

  using Type = std::unique_ptr<DIR, Deleter>;
  using Func = std::function<void(const std::string&, const std::string&)>;

  static void DFS(const std::string& rootPath, Func func);
  static Type Open(const std::string& path);
};

struct File {
  struct Deleter {
    void operator()(FILE* file);
  };
  using Type = std::unique_ptr<FILE, Deleter>;

  static Type Open(const std::string& path, const std::string& mode);
};

}  // namespace Files
}  // namespace TnHelpers