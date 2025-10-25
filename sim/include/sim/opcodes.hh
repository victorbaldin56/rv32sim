#pragma once

namespace RV32 {

enum class Opcode {
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
}
