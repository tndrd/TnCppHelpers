#pragma once

namespace TnHelpers {

template <typename T>
class UniqueValue {
 private:
  T Value;

 public:
  explicit UniqueValue(T&& value) : Value{std::move(value)} {}
  UniqueValue() : Value{} {}

  UniqueValue(const UniqueValue&) = delete;
  UniqueValue& operator=(const UniqueValue&) = delete;

  UniqueValue(UniqueValue&& rhs) {
    Value = std::move(rhs.Value);
    rhs = {};
  }

  UniqueValue& operator=(UniqueValue&& rhs) {
    std::swap(Value, rhs.Value);
    return *this;
  }

  ~UniqueValue() {}

  T& Get() { return Value; }
  const T& Get() const { return Value; }
};

}  // namespace HwBackup