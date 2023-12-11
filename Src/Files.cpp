#include "Files.hpp"

using namespace TnHelpers;
using namespace Files;

void Directory::Deleter::operator()(DIR* dir) { closedir(dir); };

auto Directory::Open(const std::string& path) -> Type {
  Type newDir = {opendir(path.c_str()), Deleter{}};
  if (!newDir.get())
    THROW_ERRNO("Failed to open directory \"" + path + "\"");
  return newDir;
}

void File::Deleter::operator()(FILE* file) { fclose(file); };

auto File::Open(const std::string& path, const std::string& mode) -> Type {
  Type newFile = {fopen(path.c_str(), mode.c_str()), Deleter{}};
  if (!newFile.get())
    THROW_ERRNO("Failed to open file \"" + path + "\"");
  return newFile;
}

void Directory::DFS(const std::string& rootPath, Func func) {
  std::stack<std::string> stk;
  stk.push(".");

  func(".", rootPath);

  while (!stk.empty()) {
    std::string nodePath = std::move(stk.top());
    stk.pop();

    std::string path = rootPath + nodePath;

    auto dir = Directory::Open(path);
    struct dirent* de;
    while ((de = readdir(dir.get())) != NULL) {
      if (strcmp(".", de->d_name) == 0 || strcmp("..", de->d_name) == 0)
        continue;

      std::string pathName = nodePath + "/" + de->d_name;

      func(nodePath, de->d_name);
      if (de->d_type == DT_DIR) stk.push(pathName);
    }
  }
}