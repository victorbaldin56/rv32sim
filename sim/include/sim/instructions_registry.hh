#pragma once

#include <cstdint>
#include <unordered_map>

#include "instruction.hh"

namespace rv32 {

class InstructionsRegistry {
 public:
  bool addInstruction(std::unique_ptr<IInstruction> inst);
  const IInstruction* get(RawInstruction raw) const;

 private:
  std::unordered_map<ExtendedOpcode, std::unique_ptr<IInstruction>> map_;
};
}
