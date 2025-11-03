// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Operands manipulation.

#pragma once

#include <format>
#include <tuple>

#include "base/bit_utils.hh"
#include "base/helpers.hh"
#include "state.hh"
#include "types.hh"

namespace rv32 {

enum class OperandKind : std::size_t {
  kRD,
  kRS1,
  kRS2,
  kRS3,
  kImmI,
  kImmS,
  kImmB,
  kImmU,
  kImmJ,

  kNumOperands,

  kShamt  // some fucking specific case
};

class Operands final {
 public:
  template <typename... Args>
  constexpr Operands(Args&&... args) noexcept
      : tuple_(std::make_tuple(std::forward<Args>(args)...)) {}

  template <OperandKind Kind>
  constexpr auto get() const noexcept {
    return std::get<helpers::underlying(Kind)>(tuple_);
  }

  constexpr auto toText() const noexcept {
    using enum OperandKind;

    // clang-format off
    return std::format(
        "RD: {}, RS1: {}, RS2: {}, RS3: {}, IMMI: 0x{:x}, IMMS: 0x{:x}, "
        "IMMB: 0x{:x}, IMMU: 0x{:x}, IMMJ: 0x{:x}",
        RegisterFile::getRegName(get<kRD>()),
        RegisterFile::getRegName(get<kRS1>()),
        RegisterFile::getRegName(get<kRS2>()),
        RegisterFile::getRegName(get<kRS3>()),
        get<kImmI>(),
        get<kImmS>(),
        get<kImmB>(),
        get<kImmU>(),
        get<kImmJ>());
    // clang-format on
  }

 private:
  using OperandsTuple = std::tuple<RegNum,      // rd
                                   RegNum,      // rs1
                                   RegNum,      // rs2
                                   RegNum,      // rs3
                                   Immediate,   // imm_i
                                   Immediate,   // imm_s
                                   Immediate,   // imm_b
                                   Immediate,   // imm_u
                                   Immediate>;  // imm_j

  static_assert(std::tuple_size_v<OperandsTuple> ==
                helpers::underlying(OperandKind::kNumOperands));

  OperandsTuple tuple_;
};

constexpr Operands extractOperands(RawInstruction r) noexcept {
  return Operands(
      // rd:
      bits::extractBits(r, 7, 11),
      // rs1:
      bits::extractBits(r, 15, 19),
      // rs2:
      bits::extractBits(r, 20, 24),
      // rs3:
      bits::extractBits(r, 27, 31),
      // imm_i:
      bits::signExtend(bits::extractBits(r, 20, 31), 12),
      // imm_s:
      bits::signExtend(
          bits::extractBits(r, 7, 11) | (bits::extractBits(r, 25, 31) << 5),
          12),
      // imm_b:
      bits::signExtend((bits::extractBits(r, 8, 11) << 1) |
                           (bits::extractBits(r, 25, 30) << 5) |
                           (bits::extractBits(r, 7, 7) << 11) |
                           (bits::extractBits(r, 31, 31) << 12),
                       13),
      // imm_u:
      bits::extractBits(r, 12, 31) << 12,
      // imm_j:
      bits::signExtend((bits::extractBits(r, 21, 30) << 1) |
                           (bits::extractBits(r, 20, 20) << 11) |
                           (bits::extractBits(r, 12, 19) << 12) |
                           (bits::extractBits(r, 31, 31) << 20),
                       21));
};

template <OperandKind Kind>
struct RegNumGetter {
  static_assert(OperandKind::kRD <= Kind && Kind <= OperandKind::kRS2);

  static RegNum get(const SimulatorState&, const Operands& operands) noexcept {
    return operands.get<Kind>();
  }
};

template <OperandKind Kind>
struct ImmGetter {
  static_assert(OperandKind::kImmI <= Kind && Kind <= OperandKind::kImmJ);

  static Word get(const SimulatorState&, const Operands& operands) noexcept {
    return operands.get<Kind>();
  }
};

// again: this is a special case
template <>
struct ImmGetter<OperandKind::kShamt> {
  static Word get(const SimulatorState& state,
                  const Operands& operands) noexcept {
    return RegNumGetter<OperandKind::kRS2>::get(state, operands);
  }
};

template <OperandKind Kind, typename Res = Word>
struct RegValueGetter {
  static Res get(const SimulatorState& state,
                 const Operands& operands) noexcept {
    return state.rf.get<Res>(RegNumGetter<Kind>::get(state, operands));
  }
};

struct PCValueGetter {
  static Addr get(const SimulatorState& state, const Operands&) noexcept {
    return state.pc.get();
  }
};
}  // namespace rv32
