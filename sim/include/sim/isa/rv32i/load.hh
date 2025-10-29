#pragma once

#include "sim/instruction_templates.hh"
#include "sim/operands.hh"

namespace rv32::rv32i {

struct OpLb {
  static constexpr std::string_view kName = "lb";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x0);

  using Result = SignedByte;
};

using Lb = LoadInstruction<OpLb>;

struct OpLh {
  static constexpr std::string_view kName = "lh";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x1);

  using Result = SignedHalf;
};

using Lh = LoadInstruction<OpLh>;

struct OpLw {
  static constexpr std::string_view kName = "lw";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x2);

  using Result = SignedWord;
};

using Lw = LoadInstruction<OpLw>;

struct OpLbu {
  static constexpr std::string_view kName = "lbu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x4);

  using Result = Byte;
};

using Lbu = LoadInstruction<OpLbu>;

struct OpLhu {
  static constexpr std::string_view kName = "lhu";
  static constexpr ExtendedOpcode kExtendedOpcode =
      Opcode3(RawOpcode::kLoad, 0x5);

  using Result = Half;
};

using Lhu = LoadInstruction<OpLhu>;
}  // namespace rv32::rv32i
