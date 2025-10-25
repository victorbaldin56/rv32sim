#pragma once

#include <cstdint>
#include <unordered_map>

#include "instruction.hh"

namespace rv32 {

class InstructionsRegistry {
 public:
  bool addInstruction(std::unique_ptr<IInstruction> inst);
  IInstruction* find(std::uint32_t ext_opcode);

 private:
  std::unordered_map<std::uint32_t, std::unique_ptr<IInstruction>> map_;
};
}
