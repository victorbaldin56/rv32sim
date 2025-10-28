#pragma once

#include "base/bit_utils.hh"
#include "memory.hh"
#include "register_file.hh"

namespace rv32 {

enum class ExecutionResult { kOk, kExit, kMisalignment };

class ProgramCounter final {
 public:
  static constexpr std::size_t kInstructionAlignment = 4;

  Addr get() const noexcept { return pc_; }
  Addr getNext() const noexcept { return pc_ + sizeof(RawInstruction); }
  ExecutionResult set(Addr ja) {
    pc_ = ja;
    return bits::isAligned(pc_, kInstructionAlignment)
               ? ExecutionResult::kOk
               : ExecutionResult::kMisalignment;
  }

  ProgramCounter& operator++() noexcept {
    pc_ = getNext();
    return *this;
  }

  ProgramCounter operator++(int) noexcept {
    ProgramCounter p = *this;
    pc_ = getNext();
    return p;
  }

 private:
  Addr pc_ = 0;
};

struct SimulatorState {
  RegisterFile rf;
  Memory mem;
  ProgramCounter pc;

  static ExecutionResult ecall(SimulatorState& state);

  enum class Syscall : Word {
    kRead = 63,
    kWrite = 64,
    kExit = 93,
  };
};
}
