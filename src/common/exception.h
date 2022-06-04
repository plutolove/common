#pragma once
#include <vector>

#include "exception_base.h"
#include "fmt/format.h"
namespace common {

class Exception : public ExceptionBase {
 public:
  Exception() = default;
  Exception(const std::string &msg, int code, bool remote_ = false)
      : ExceptionBase(msg, code), remote(remote_) {}

  Exception(int code, const std::string &message) : Exception(message, code) {}

  // Format message with fmt::format, like the logging functions.
  template <typename... Args>
  Exception(int code, fmt::format_string<Args...> fmt, Args &&...args)
      : Exception(fmt::format(fmt, std::forward<Args>(args)...), code) {}

  Exception *clone() const override { return new Exception(*this); }

  void rethrow() const override { throw *this; }

  const char *name() const noexcept override { return "Common::Exception"; }
  const char *what() const noexcept override { return message().data(); }

  /// Add something to the existing message.
  template <typename... Args>
  void addMessage(fmt::format_string<Args...> format, Args &&...args) {
    extendedMessage(fmt::format(format, std::forward<Args>(args)...));
  }

  void addMessage(const std::string &message) { extendedMessage(message); }

  /// Used to distinguish local exceptions from the one that was received from
  /// remote node.
  void setRemoteException(bool remote_ = true) { remote = remote_; }
  bool isRemoteException() const { return remote; }

 private:
  bool remote = false;
  const char *className() const noexcept override {
    return "Common::Exception";
  }
};

}  // namespace common