#pragma once

#include <poll.h>

#include <vector>

#include "Pipe.hpp"
#include "UniqueValue.hpp"

namespace TnHelpers {

struct Selector {
 public:
  using IdT = UniqueValue<size_t>;

 public:
  struct Alarmer {
   private:
    IPC::Pipe Pipe;
    IdT SelectorId;

   public:
    Alarmer();

    Alarmer(Alarmer&&) = default;
    Alarmer& operator=(Alarmer&&) = default;

    void RegisterAt(Selector& selector);
    void Alarm();
    bool Triggered(const Selector& selector);
  };

 private:
  std::vector<pollfd> PollFds;

 public:
  IdT Register(int fd, short events);
  void Wait();

  short GetEvents(const IdT& i) const;
};
}  // namespace TnHelpers