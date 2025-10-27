#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

#include <cerrno>
#include <cstring>

#include "base/mmaped_file.hh"

namespace rv32 {

UniqueMmap MmapedFile::mmapWholeFile(const UniqueFD& fd,
                                     const std::filesystem::path& path) {
  std::size_t sz = getFileStats(fd, path).st_size;

  try {
    return makeUniqueMmap(nullptr, sz, PROT_READ, MAP_PRIVATE, fd.get(), 0);
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
