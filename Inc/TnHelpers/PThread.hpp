#pragma once

#include <assert.h>
#include <pthread.h>
#include <signal.h>

#include <iostream>

#include "Exception.hpp"
#include "StderrWarning.hpp"
#include "UniqueValue.hpp"

namespace TnHelpers {
namespace PThread {

class Mutex final : public UniqueValue<pthread_mutex_t> {
 public:
  Mutex();
  ~Mutex();

  Mutex(Mutex&&) = default;
  Mutex& operator=(Mutex&&) = default;

  void Lock();
  void Unlock();
};

class Cond final : public UniqueValue<pthread_cond_t> {
 public:
  Cond();
  ~Cond();
  void Wait(Mutex& mutex);
  void TimedWait(Mutex& mutex, const timespec& ts);
  void Signal();
};

class Thread final {
 public:
  using Routine = void* (*)(void*);

 private:
  UniqueValue<bool> IsJoined;
  UniqueValue<pthread_t> Impl;

 public:
  Thread(Routine target, void* args);
  Thread();
  ~Thread();

  Thread(Thread&&) = default;
  Thread& operator=(Thread&&) = default;

 public:
  void Join();
  void Kill(int sig);
  void SetSigmask(int how, const sigset_t& set);
};
}  // namespace PThread
}  // namespace TnHelpers