#pragma once

#include <cstdint>
#include <tuple>
#include <unordered_map>

#include "instruction.hh"

namespace rv32 {

class InstructionsRegistry {
 public:
  void add(std::unique_ptr<IInstruction> inst);
  const IInstruction* get(RawInstruction raw) const noexcept;

 private:
  std::unordered_map<ExtendedOpcode, std::unique_ptr<IInstruction>> map_;
};
}
