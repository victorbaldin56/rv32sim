// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Important types

#pragma once

#include <cstdint>
#include <type_traits>

namespace rv32 {

using Addr = std::uint32_t;
using Size = std::uint32_t;

using Byte = std::uint8_t;
using HalfWord = std::uint16_t;
using Word = std::uint32_t;

using SignedWord = std::make_signed_t<Word>;

using RawInstruction = std::uint32_t;

using Immediate = std::int32_t;
using RegNum = std::uint32_t;
}  // namespace rv32
