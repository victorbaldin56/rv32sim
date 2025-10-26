// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Important types

#pragma once

#include <cstdint>

namespace rv32 {

using Addr = std::uint32_t;
using Size = std::uint32_t;

using Byte = std::uint8_t;
using HalfWord = std::uint16_t;
using Word = std::uint32_t;

using RawInstruction = std::uint32_t;
using ExtendedOpcode = std::uint32_t;
}  // namespace rv32
