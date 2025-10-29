#pragma once

#include "sim/instruction_templates.hh"
#include "sim/operands.hh"

namespace rv32::rv32i {

struct OpSb {
  static constexpr std::string_view kName = "sb";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kStore, 0x0);

  using Emitted = Byte;
};

using Sb = StoreInstruction<OpSb>;

struct OpSh {
  static constexpr std::string_view kName = "sh";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kStore, 0x1);

  using Emitted = Half;
};

using Sh = StoreInstruction<OpSh>;

struct OpSw {
  static constexpr std::string_view kName = "sw";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kStore, 0x2);

  using Emitted = Word;
};

using Sw = StoreInstruction<OpSw>;
}  // namespace rv32::rv32i
