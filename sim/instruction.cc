// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// TODO

#include "sim/instruction.hh"

#include "base/bit_utils.hh"
#include "sim/opcodes.hh"

namespace rv32 {

std::unique_ptr<IInstruction> IInstruction::create(RawInstruction raw) {
  Opcode opcode = static_cast<Opcode>(bits::bits(raw, 0, 6));
  switch (opcode) {
    case Opcode::kOp:
      // R-type
      break;
    case Opcode::kOpImm:
    case Opcode::kLoad:
    case Opcode::kJalr:
    case Opcode::kSystem:
    case Opcode::kMiscMem:
      // I-type
      break;
    case Opcode::kStore:
      // S-type
      break;
    case Opcode::kBranch:
      // B-type
      break;
    case Opcode::kLui:
    case Opcode::kAuipc:
      // U-type
      break;
    case Opcode::kJal:
      // J-type
      break;
    default:
      // ILLEGAL
  }
}
}  // namespace rv32
