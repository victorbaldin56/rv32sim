// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// Basic constants

#include "types.hh"

#pragma once

// TODO: как то поделить
namespace RV32::Config {

constexpr Addr kStackTop = 0x7fffffff;

constexpr Size kPageSize = 0x1000;
constexpr Size kArgMax = 0x20 * kPageSize;  // as in Linux

constexpr Size kStackAlignment = 0x10;
}
