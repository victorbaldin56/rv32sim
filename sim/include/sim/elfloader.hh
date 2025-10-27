// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// ELF file loading methods.

#pragma once

#include <filesystem>
#include <stdexcept>
#include <string>

#include "base/mmaped_file.hh"
#include "gelf.h"
#include "memory.hh"

namespace rv32 {

class ElfLoader final {
 public:
  ElfLoader(const std::filesystem::path& path);
  void load(Memory& mem) const;

  Addr getEntryPC() const noexcept { return elf_header_.e_entry; }

  class Error : public std::runtime_error {
   public:
    using std::runtime_error::runtime_error;
  };

 private:
  MmapedFile mmaped_elf_;
  std::uint8_t* elf_image_;
  Elf32_Ehdr elf_header_;
  Byte* program_headers_start_;

  void checkElfHeader() const;
};
}  // namespace rv32
