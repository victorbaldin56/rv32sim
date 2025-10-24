#pragma once

#include <cstdint>
#include <filesystem>
#include <stdexcept>

namespace RV32 {

class ScopedMmap final {
 public:
  ScopedMmap(const std::filesystem::path& path);
  ~ScopedMmap();

  std::uint8_t* data() const noexcept { return data_; }
  std::size_t size() const noexcept { return sz_; }

  class Error : public std::runtime_error {
   public:
    using std::runtime_error::runtime_error;
  };

 private:
  std::uint8_t* data_;
  std::size_t sz_;
  int fd_;
};
}  // namespace RV32
