// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// ELF file loading implementation.

#include "sim/elfloader.hh"

#include "base/scoped_mmap.hh"

namespace RV32 {

ElfLoader::ElfLoader(const std::filesystem::path& path) : image_(path) {
  if (image_.size() < sizeof(elf_header_)) {
    throw Error("File too short");
  }

  std::memcpy(&elf_header_, image_.data(), sizeof(elf_header_));
  checkElfHeader();

  if (image_.size() <
      elf_header_.e_phoff + elf_header_.e_phnum * sizeof(Elf32_Phdr)) {
    throw Error("File too short");
  }
  program_headers_start_ = image_.data() + elf_header_.e_shoff;
}

void ElfLoader::load(Memory& mem) {}

void ElfLoader::checkElfHeader() const {
  if (std::memcmp(elf_header_.e_ident + EI_MAG0, ELFMAG, SELFMAG) != 0) {
    throw Error("Not an ELF file");
  }

  if (elf_header_.e_ident[EI_CLASS] != ELFCLASS32) {
    throw Error("ELF must be 32-bit");
  }
  if (elf_header_.e_ident[EI_DATA] != ELFDATA2LSB) {
    throw Error("Elf must be little-endian");
  }
  if (elf_header_.e_ident[EI_VERSION] != EV_CURRENT) {
    throw Error("Invalid ELF header version");
  }
  if (elf_header_.e_ident[EI_OSABI] != ELFOSABI_SYSV) {
    throw Error("ELF OS/ABI must be System V");
  }
  if (elf_header_.e_ident[EI_ABIVERSION] != 0) {
    throw Error("Invalid ELF OS/ABI version");
  }

  if (elf_header_.e_type != ET_EXEC) {
    throw Error("ELF must be executable");
  }
  if (elf_header_.e_machine != EM_RISCV) {
    throw Error("ELF machine must be RISCV");
  }
}
}  // namespace RV32
