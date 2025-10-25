#include "base/scoped_mmap.hh"

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>

namespace rv32 {

ScopedMmap::ScopedMmap(const std::filesystem::path& path) {
  using namespace std::string_literals;

  fd_ = open(path.c_str(), O_RDONLY);
  if (fd_ == -1) {
    throw Error("open() failed for file \""s + path.string() + "\": "s +
                std::string(std::strerror(errno)));
  }

  struct stat stbuf;
  if (fstat(fd_, &stbuf) == -1) {
    throw Error("stat() failed for file \""s + path.string() + "\": "s +
                std::string(std::strerror(errno)));
  }
  sz_ = stbuf.st_size;

  void* p = mmap(nullptr, sz_, PROT_READ, MAP_PRIVATE, fd_, 0);
  if (p == MAP_FAILED) {
    throw Error("mmap() failed for file \""s + path.string() + "\": "s +
                std::string(std::strerror(errno)));
  }

  data_ = static_cast<std::uint8_t*>(p);
}

ScopedMmap::~ScopedMmap() {
  munmap(data_, sz_);
  close(fd_);
}
}  // namespace rv32
