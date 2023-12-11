#include "Selector.hpp"

using namespace TnHelpers;

auto Selector::Register(int fd, short events) -> IdT {
  pollfd newPollFd;

  newPollFd.fd = fd;
  newPollFd.events = events;

  PollFds.push_back(newPollFd);
  return IdT{PollFds.size() - 1};
}

void Selector::Wait() {
  int ret = poll(PollFds.data(), PollFds.size(), -1);
  if (ret < 0) THROW_ERRNO("poll()");
}

short Selector::GetEvents(const IdT& i) const {
  return PollFds.at(i.Get()).revents;
}

Selector::Alarmer::Alarmer() : Pipe{O_NONBLOCK} {}

void Selector::Alarmer::RegisterAt(Selector& selector) {
  SelectorId = selector.Register(Pipe.ReadFd(), POLLIN);
}

void Selector::Alarmer::Alarm() {
  int dummy = 42;
  int ret = write(Pipe.WriteFd(), &dummy, 1);
  if (ret < 0) THROW_ERRNO("write()");
}

bool Selector::Alarmer::Triggered(const Selector& selector) {
  return selector.GetEvents(SelectorId) & POLLIN;
}