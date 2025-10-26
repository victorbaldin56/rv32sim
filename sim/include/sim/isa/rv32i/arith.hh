#pragma once

#include "sim/basic_instruction.hh"
#include "sim/opcodes.hh"
#include "sim/operands.hh"

namespace rv32::rv32i {

struct OpLui {
  static constexpr std::string_view kName = "lui";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kLui);

  static Word eval(Word imm) noexcept { return imm; }
};
using Lui = ArithInstruction<OpLui, ImmGetter<OperandKind::kImmU>>;
}
