#pragma once

#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>

#include <cstring>
#include <filesystem>
#include <format>

#include "boost/scope/unique_fd.hpp"
#include "boost/scope/unique_resource.hpp"

namespace rv32 {

template <typename T>
inline auto produceSyscallErrorMessage(const std::string& syscall_name,
                                       const std::string& arg_name,
                                       const T& arg_value) {
  return std::format("{}() failed for {} \"{}\": {}", syscall_name, arg_name,
                     arg_value, std::strerror(errno));
}

class FDOpenError : public std::runtime_error {
 public:
  FDOpenError(const std::filesystem::path& path)
      : std::runtime_error(
            produceSyscallErrorMessage("open", "file", path.string())) {}
};

using UniqueFD = boost::scope::unique_fd;

inline UniqueFD makeUniqueFD(const std::filesystem::path& path, int flags) {
  UniqueFD fd(open(path.c_str(), flags));
  if (!fd.allocated()) {
    throw FDOpenError(path);
  }
  return fd;
}

struct MmapDeleter {
  std::size_t len;

  void operator()(void* p) const noexcept { munmap(p, len); }
};

struct MmapResourceTraits {
  static bool is_allocated(const void* p) noexcept { return p != MAP_FAILED; }
  static void* make_default() noexcept { return MAP_FAILED; }
};

using UniqueMmap =
    boost::scope::unique_resource<void*, MmapDeleter, MmapResourceTraits>;

class MmapError : public std::runtime_error {
 public:
  MmapError(int fd)
      : std::runtime_error(
            produceSyscallErrorMessage("mmap", "descriptor", fd)) {}
};

inline UniqueMmap makeUniqueMmap(void* addr, std::size_t len, int prot,
                                 int flags, int fd, off_t offset) {
  UniqueMmap map(mmap(addr, len, prot, flags, fd, offset), MmapDeleter(len));
  if (!map.allocated()) {
    throw MmapError(fd);
  }
  return map;
}

class MmapedFile final {
 public:
  MmapedFile() noexcept = default;
  MmapedFile(const std::filesystem::path& path, int open_flags = O_RDONLY,
             void* addr = nullptr, int prot = PROT_READ,
             int mmap_flags = MAP_PRIVATE, off_t offset = 0)
      : fd_(makeUniqueFD(path, open_flags)),
        mmap_(mmapWholeFile(fd_, path, open_flags, addr, prot, mmap_flags,
                            offset)) {}

  void* data() noexcept { return mmap_.get(); }
  const void* data() const noexcept { return mmap_.get(); }
  std::size_t size() const noexcept { return mmap_.get_deleter().len; }

  class Error : public std::runtime_error {
   public:
    using std::runtime_error::runtime_error;
  };

 private:
  UniqueFD fd_;
  UniqueMmap mmap_;

  static UniqueMmap mmapWholeFile(
      const UniqueFD& fd,
      const std::filesystem::path& path,  // path for error reporting
      int open_flags, void* addr, int prot, int mmap_flags, off_t offset);
  static struct stat getFileStats(const UniqueFD& fd,
                                  const std::filesystem::path& path);
};
}  // namespace rv32
