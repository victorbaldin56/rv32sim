#pragma once

#include <tuple>

#include "base/bit_utils.hh"
#include "base/helpers.hh"
#include "state.hh"
#include "types.hh"

namespace rv32 {

enum class OperandKind : std::size_t {
  kRd,
  kRs1,
  kRs2,
  kImmI,
  kImmS,
  kImmB,
  kImmU,
  kImmJ,

  kNumOperands
};

using Operands = std::tuple<RegNum,      // rd
                            RegNum,      // rs1
                            RegNum,      // rs2
                            Immediate,   // imm_i
                            Immediate,   // imm_s
                            Immediate,   // imm_b
                            Immediate,   // imm_u
                            Immediate>;  // imm_j

static_assert(std::tuple_size_v<Operands> ==
              helpers::underlying(OperandKind::kNumOperands));

constexpr Operands extractOperands(RawInstruction r) noexcept {
  return {// rd:
          bits::extractBits(r, 7, 11),
          // rs1:
          bits::extractBits(r, 15, 19),
          // rs2:
          bits::extractBits(r, 20, 24),
          // imm_i:
          bits::signExtend(bits::extractBits(r, 12, 20), 11),
          // imm_s:
          bits::signExtend(
              bits::extractBits(r, 7, 11) | (bits::extractBits(r, 25, 31) << 5),
              11),
          // imm_b:
          bits::signExtend((bits::extractBits(r, 8, 11) << 1) |
                               (bits::extractBits(r, 25, 30) << 5) |
                               (bits::extractBits(r, 7, 7) << 11) |
                               (bits::extractBits(r, 31, 31) << 12),
                           12),
          // imm_u:
          bits::signExtend(bits::extractBits(r, 12, 31) << 12, 31),
          // imm_j:
          bits::signExtend((bits::extractBits(r, 21, 30) << 1) |
                               (bits::extractBits(r, 20, 20) << 11) |
                               (bits::extractBits(r, 12, 19) << 12) |
                               (bits::extractBits(r, 31, 31) << 20),
                           20)};
};

template <OperandKind kind>
struct ImmGetter {
  static_assert(OperandKind::kImmI <= kind && kind <= OperandKind::kImmJ);

  static Word get(const SimulatorState&, const Operands& operands) noexcept {
    return std::get<helpers::underlying(kind)>(operands);
  }
};

template <OperandKind kind>
struct RegNumGetter {
  static_assert(OperandKind::kRd <= kind && kind <= OperandKind::kRs2);

  static RegNum get(const SimulatorState&, const Operands& operands) noexcept {
    return std::get<helpers::underlying(kind)>(operands);
  }
};

template <OperandKind kind>
struct RegValueGetter {
  static Word get(const SimulatorState& state,
                  const Operands& operands) noexcept {
    return state.rf.get(RegNumGetter<kind>::get(state, operands));
  }
};
}  // namespace rv32
