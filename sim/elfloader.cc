// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// ELF file loading implementation.

#include "sim/elfloader.hh"

namespace rv32 {

ElfLoader::ElfLoader(const std::filesystem::path& path)
    : mmaped_elf_(path),
      elf_image_(static_cast<std::uint8_t*>(mmaped_elf_.data())),
      logger_(spdlog::stderr_color_mt("ElfLoader")) {
  logger_->set_level(
      static_cast<spdlog::level::level_enum>(SPDLOG_ACTIVE_LEVEL));

  if (mmaped_elf_.size() < sizeof(elf_header_)) {
    throw Error("File too short");
  }

  std::memcpy(&elf_header_, elf_image_, sizeof(elf_header_));
  checkElfHeader();

  if (mmaped_elf_.size() <
      elf_header_.e_phoff + elf_header_.e_phnum * elf_header_.e_phentsize) {
    throw Error("File too short");
  }
  program_headers_start_ = elf_image_ + elf_header_.e_phoff;
  SPDLOG_LOGGER_TRACE(logger_,
                      "Parsed ELF: program headers table starts at 0x{:x}",
                      elf_header_.e_phoff);
}

void ElfLoader::load(Memory& mem) const {
  std::uint8_t* phdr = program_headers_start_;
  for (std::size_t i = 0; i < elf_header_.e_phnum;
       ++i, phdr += elf_header_.e_phentsize) {  // considering strict aliasing
    Elf32_Phdr hdr;
    std::memcpy(&hdr, phdr, sizeof(hdr));

    if (hdr.p_type == PT_LOAD) {
      SPDLOG_LOGGER_TRACE(logger_,
                          "Loading section #{}, p_vaddr: "
                          "0x{:x}, p_filesz: 0x{:x}, p_memsz: 0x{:x}",
                          i, hdr.p_vaddr, hdr.p_filesz, hdr.p_memsz);

      if (hdr.p_vaddr + hdr.p_filesz > mem.size()) {
        throw Error(
            std::format("Cannot load section at offset 0x{:x}: section too big",
                        hdr.p_offset));
      }
      mem.copy(hdr.p_vaddr, elf_image_ + hdr.p_offset, hdr.p_filesz);

      if (hdr.p_memsz > hdr.p_filesz) {
        if (hdr.p_vaddr + hdr.p_memsz > mem.size()) {
          throw Error(std::format("Cannot memset at offset {:x}: size to big",
                                  hdr.p_offset));
        }
        mem.memset(hdr.p_vaddr + hdr.p_filesz, 0, hdr.p_memsz - hdr.p_filesz);
      }
    }
    // TODO: properly handle missing cases
  }
}

void ElfLoader::checkElfHeader() const {
  if (std::memcmp(&elf_header_.e_ident[EI_MAG0], ELFMAG, SELFMAG) != 0) {
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
