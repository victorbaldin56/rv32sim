#pragma once

#include "base/bit_utils.hh"
#include "memory.hh"
#include "register_file.hh"

namespace rv32 {

enum class ExecutionResult { kOk, kExit, kMisalignment };

class ProgramCounter final {
 public:
  static constexpr std::size_t kInstructionAlignment = 4;

  enum class SetStatus { kOk, kMisalignment };

  Addr get() const noexcept { return pc_; }
  SetStatus set(Addr ja) {
    pc_ = ja;
    return bits::isAligned(pc_, kInstructionAlignment)
               ? SetStatus::kOk
               : SetStatus::kMisalignment;
  }

  ProgramCounter& operator++() noexcept {
    pc_ += sizeof(RawInstruction);
    return *this;
  }

  ProgramCounter operator++(int) noexcept {
    ProgramCounter p = *this;
    pc_ += sizeof(RawInstruction);
    return p;
  }

 private:
  Addr pc_ = 0;
};

struct SimulatorState {
  RegisterFile rf;
  Memory mem;
  ProgramCounter pc;
};
}
