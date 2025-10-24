// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// ELF file loading methods.

#pragma once

#include <filesystem>
#include <stdexcept>
#include <string>

#include "base/scoped_mmap.hh"
#include "gelf.h"
#include "memory.hh"

namespace RV32 {

class ElfLoader final {
 public:
  ElfLoader(const std::filesystem::path& path);
  void load(Memory& mem);

  class Error : public std::runtime_error {
   public:
    using std::runtime_error::runtime_error;
  };

 private:
  ScopedMmap image_;
  Elf32_Ehdr elf_header_;
  std::uint8_t* program_headers_start_;

  void checkElfHeader() const;
};
}
