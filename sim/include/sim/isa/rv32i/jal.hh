#pragma once

#include "sim/basic_instruction.hh"
#include "sim/operands.hh"

namespace rv32::rv32i {

template <typename Op, typename... ValueGetters>
class JalInstruction final : public BasicInstruction<Op> {
 public:
  ExecutionResult execute(SimulatorState& state,
                          const Operands& operands) const override {
    ProgramCounter current_pc = state.pc++;
    ExecutionResult res =
        current_pc.set(Op::getNextPC(ValueGetters::get(state, operands)...));
    state.rf.set(RegNumGetter<OperandKind::kRD>::get(state, operands),
                 state.pc.get());
    return res;
  }
};

struct OpJal {
  static constexpr std::string_view kName = "jal";
  static constexpr ExtendedOpcode kExtendedOpcode = Opcode(RawOpcode::kJal);

  static Addr getNextPC(Addr pc, Word offset) noexcept { return pc + offset; }
};

using Jal = JalInstruction<OpJal, PCValueGetter, ImmGetter<OperandKind::kImmI>>;

struct OpJalr {
  static constexpr std::string_view kName = "jalr";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kJalr, 0x0);

  static Addr getNextPC(Word rs1, Word offset) noexcept {
    return (rs1 + offset) & 0xfffffffe;
  }
};

using Jalr = JalInstruction<OpJalr, RegValueGetter<OperandKind::kRS1>,
                            ImmGetter<OperandKind::kImmI>>;
}  // namespace rv32::rv32i