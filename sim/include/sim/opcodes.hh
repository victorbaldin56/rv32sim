#pragma once

#include <cstdint>
#include <tuple>
#include <unordered_map>
#include <variant>

#include "base/bit_utils.hh"
#include "base/helpers.hh"
#include "types.hh"

namespace rv32 {

enum class RawOpcode : std::uint8_t {
  kLoad = 0x3,
  kMiscMem = 0xf,
  kOpImm = 0x13,
  kAuipc = 0x17,
  kStore = 0x23,
  kOp = 0x33,
  kLui = 0x37,
  kBranch = 0x63,
  kJalr = 0x67,
  kJal = 0x6f,
  kSystem = 0x73,
};

template <typename Opcode>
struct ExtendedOpcodeHash {
  std::size_t operator()(const Opcode& opcode) const noexcept {
    return std::hash<RawInstruction>()(static_cast<RawInstruction>(opcode));
  }
};

class Opcode {
 public:
  constexpr Opcode(RawOpcode opcode)
      : opcode_(static_cast<RawInstruction>(opcode)) {}
  constexpr Opcode(RawInstruction raw) noexcept
      : opcode_(bits::extractBits(raw, 0, 6)) {}

  constexpr operator RawInstruction() const noexcept { return opcode_; }

 private:
  const RawInstruction opcode_;
};

class Opcode3 : public Opcode {
 public:
  constexpr Opcode3(RawOpcode opcode, std::uint8_t funct3)
      : Opcode(opcode), funct3_(funct3) {}
  constexpr Opcode3(RawInstruction raw) noexcept
      : Opcode(raw), funct3_(bits::extractBits(raw, 12, 14)) {}

  constexpr operator RawInstruction() const noexcept {
    return Opcode::operator RawInstruction() | (funct3_ << 12);
  }

 private:
  const RawInstruction funct3_;
};

class Opcode37 : public Opcode3 {
 public:
  constexpr Opcode37(RawOpcode opcode, std::uint8_t funct3, std::uint8_t funct7)
      : Opcode3(opcode, funct3), funct7_(funct7) {}
  constexpr Opcode37(RawInstruction raw) noexcept
      : Opcode3(raw), funct7_(bits::extractBits(raw, 25, 31)) {}

  constexpr operator RawInstruction() const noexcept {
    return Opcode3::operator RawInstruction() | (funct7_ << 25);
  }

 private:
  const RawInstruction funct7_;
};

using ExtendedOpcodeTuple = std::tuple<Opcode, Opcode3, Opcode37>;
using ExtendedOpcode = helpers::ToVariantT<ExtendedOpcodeTuple>;

class ExtendedOpcodesCreator {
 public:
  static constexpr ExtendedOpcodeTuple create(RawInstruction r) {
    return TupleFiller<ExtendedOpcodeTuple>::fill(r);
  }

 private:
  template <typename Tuple>
  struct TupleFiller;

  template <typename... Types>
  struct TupleFiller<std::tuple<Types...>> {
    static constexpr std::tuple<Types...> fill(RawInstruction r) {
      return std::make_tuple(Types(r)...);
    }
  };
};
}
