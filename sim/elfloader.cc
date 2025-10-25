// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// ELF file loading implementation.

#include "sim/elfloader.hh"

#include "base/scoped_mmap.hh"

namespace rv32 {

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

void ElfLoader::load(Memory& mem) const {
  Byte* phdr = program_headers_start_;
  for (std::size_t i = 0; i < elf_header_.e_phnum;
       ++i, phdr += sizeof(Elf32_Phdr)) {  // considering strict aliasing
    Elf32_Phdr hdr;
    std::memcpy(&hdr, phdr, sizeof(hdr));

    if (hdr.p_type == PT_LOAD) {
      mem.copy(hdr.p_vaddr, image_.data() + hdr.p_offset, hdr.p_filesz);

      if (hdr.p_memsz > hdr.p_filesz) {
        mem.memset(hdr.p_vaddr + hdr.p_filesz, 0, hdr.p_memsz - hdr.p_filesz);
      }
    }
    // TODO: properly handle missing cases
  }
}

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
}  // namespace rv32
