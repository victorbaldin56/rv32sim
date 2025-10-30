// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// RAII file mapping.

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>

#include "base/mmaped_file.hh"

namespace rv32 {

UniqueMmap MmapedFile::mmapWholeFile(const UniqueFD& fd,
                                     const std::filesystem::path& path,
                                     int open_flags, void* addr, int prot,
                                     int mmap_flags, off_t offset) {
  std::size_t sz = getFileStats(fd, path).st_size;

  try {
    return makeUniqueMmap(addr, sz, prot, mmap_flags, fd.get(), offset);
  } catch (MmapError& e) {
    throw Error(produceSyscallErrorMessage(
        "mmap", "file", path.string()));  // more concrete report
  }
}

struct stat MmapedFile::getFileStats(const UniqueFD& fd,
                                     const std::filesystem::path& path) {
  struct stat stbuf;
  if (fstat(fd.get(), &stbuf) == -1) {
    throw Error(produceSyscallErrorMessage("fstat", "file", path.string()));
  }

  return stbuf;
}
}  // namespace rv32
