// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Basic constants

#include "types.hh"

#pragma once

// TODO: как то поделить
namespace rv32::config {

constexpr Addr kStackTop = 0x7fffffff;

constexpr Size kPageSize = 0x1000;
constexpr Size kArgMax = 0x20 * kPageSize;  // as in Linux

constexpr Size kStackAlignment = 0x10;
}  // namespace rv32::config
