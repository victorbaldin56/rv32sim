// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Opcode manipulation.

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
  // rv32im
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

  // rv32imf
  kLoadFp = 0x07,
  kStoreFp = 0x27,
  kMAdd = 0x43,
  kMSub = 0x47,
  kNMAdd = 0x4f,
  kNMSub = 0x4b,
  kOpFp = 0x53,
};

template <typename Opcode>
struct ExtendedOpcodeHash {
  std::size_t operator()(const Opcode& opcode) const noexcept {
    return std::hash<RawInstruction>()(static_cast<RawInstruction>(opcode));
  }
};

class Opcode {
 public:
  Opcode(RawOpcode opcode) noexcept
      : opcode_(static_cast<RawInstruction>(opcode)) {}
  Opcode(RawInstruction raw) noexcept : opcode_(bits::extractBits(raw, 0, 6)) {}

  operator RawInstruction() const noexcept { return opcode_; }

  // no virtual destructor : for sure we are not gonna use base pointers to
  // delete derived classes

 private:
  const RawInstruction opcode_;
};

class Opcode3 : public virtual Opcode {
 public:
  Opcode3(RawOpcode opcode, std::uint8_t funct3) noexcept
      : Opcode(opcode), funct3_(funct3) {}
  Opcode3(RawInstruction raw) noexcept
      : Opcode(raw), funct3_(bits::extractBits(raw, 12, 14)) {}

  operator RawInstruction() const noexcept {
    return Opcode::operator RawInstruction() | (funct3_ << 12);
  }

 private:
  const RawInstruction funct3_;
};

class Opcode5 : public virtual Opcode {
 public:
  Opcode5(RawOpcode opcode, std::uint8_t funct5) noexcept
      : Opcode(opcode), funct5_(funct5) {}
  Opcode5(RawInstruction r) noexcept
      : Opcode(r), funct5_(bits::extractBits(r, 27, 31)) {}

  operator RawInstruction() const noexcept {
    return Opcode::operator RawInstruction() | (funct5_ << 27);
  }

 private:
  const RawInstruction funct5_;
};

class Opcode7 : public virtual Opcode {
 public:
  Opcode7(RawOpcode opcode, std::uint8_t funct7) noexcept
      : Opcode(opcode), funct7_(funct7) {}
  Opcode7(RawInstruction r) noexcept
      : Opcode(r), funct7_(bits::extractBits(r, 25, 31)) {}

  operator RawInstruction() const noexcept {
    return Opcode::operator RawInstruction() | (funct7_ << 25);
  }

 private:
  const RawInstruction funct7_;
};

class Opcode35 : public Opcode3, public Opcode5 {
 public:
  Opcode35(RawOpcode opcode, std::uint8_t funct3, std::uint8_t funct5) noexcept
      : Opcode(opcode), Opcode3(opcode, funct3), Opcode5(opcode, funct5) {}
  Opcode35(RawInstruction raw) noexcept
      : Opcode(raw), Opcode3(raw), Opcode5(raw) {}

  operator RawInstruction() const noexcept {
    return Opcode3::operator RawInstruction() |
           Opcode5::operator RawInstruction();
  }
};

class Opcode37 : public Opcode3, public Opcode7 {
 public:
  Opcode37(RawOpcode opcode, std::uint8_t funct3, std::uint8_t funct7) noexcept
      : Opcode(opcode), Opcode3(opcode, funct3), Opcode7(opcode, funct7) {}
  Opcode37(RawInstruction raw) noexcept
      : Opcode(raw), Opcode3(raw), Opcode7(raw) {}

  operator RawInstruction() const noexcept {
    return Opcode3::operator RawInstruction() |
           Opcode7::operator RawInstruction();
  }
};

class Opcode5RS2 : public Opcode5 {
 public:
  Opcode5RS2(RawOpcode opcode, std::uint8_t funct5, std::uint8_t rs2) noexcept
      : Opcode(opcode), Opcode5(opcode, funct5), rs2_(rs2) {}
  Opcode5RS2(RawInstruction raw) noexcept
      : Opcode(raw), Opcode5(raw), rs2_(bits::extractBits(raw, 20, 24)) {}

  operator RawInstruction() const noexcept {
    return Opcode5::operator RawInstruction() | (rs2_ << 20);
  }

 private:
  const RawInstruction rs2_;
};

class Opcode35RS2 : public Opcode3, public Opcode5RS2 {
 public:
  Opcode35RS2(RawOpcode opcode, std::uint8_t funct3, std::uint8_t funct5,
              std::uint8_t rs2) noexcept
      : Opcode(opcode),
        Opcode3(opcode, funct3),
        Opcode5RS2(opcode, funct5, rs2) {}
  Opcode35RS2(RawInstruction raw) noexcept
      : Opcode(raw), Opcode3(raw), Opcode5RS2(raw) {}

  operator RawInstruction() const noexcept {
    return Opcode3::operator RawInstruction() |
           Opcode5RS2::operator RawInstruction();
  }
};

using ExtendedOpcodeTuple =
    std::tuple<Opcode, Opcode3, Opcode5, Opcode37, Opcode35, Opcode5RS2,
               Opcode35RS2, RawInstruction>;
using ExtendedOpcode = helpers::ToVariantT<ExtendedOpcodeTuple>;

class ExtendedOpcodesCreator final {
 public:
  static ExtendedOpcodeTuple create(RawInstruction r) noexcept {
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
