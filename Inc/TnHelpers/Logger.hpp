#pragma once

#include <assert.h>
#include <sys/time.h>
#include <time.h>

#include <memory>
#include <ostream>

#include "Exception.hpp"
#include "PThread.hpp"

namespace TnHelpers {

class Logger final {
 public:
  // using StreamPtr = std::unique_ptr<std::ostream>;
  using StreamPtr = UniqueValue<std::ostream*>;

 public:
  enum class LoggingLevel { Info, Warn, Error, Quiet };

 private:
  StreamPtr StreamImpl;
  PThread::Mutex Mutex;

 public:
  Logger(StreamPtr&& stream);

  std::ostream& Start(LoggingLevel level);
  void End();

  std::ostream& StartInfo();
  std::ostream& StartWarning();
  std::ostream& StartError();

  static Logger CreateDefault();

  Logger(Logger&&) = default;
  Logger& operator= (Logger&&) = default;

 private:
  void PutTimestamp();
  void PutLevel(LoggingLevel level);
  void PutColor(LoggingLevel level);
  void ResetColor();

  static const char* LevelToString(LoggingLevel level);
  static const char* LevelToColor(LoggingLevel level);
  static const char* ResetColorStr();
};

}  // namespace HwBackup

#define LOG_INFO(logger, msg) \
  {logger.StartInfo() << msg;  \
  logger.End();}
#define LOG_WARN(logger, msg)                \
  {logger.StartWarning() << LOC_STAMP << msg; \
  logger.End();}
#define LOG_ERROR(logger, msg)             \
  {logger.StartError() << LOC_STAMP << msg; \
  logger.End();}
