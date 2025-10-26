#pragma once

#include "register_file.hh"
#include "memory.hh"

namespace rv32 {

struct SimulatorState {
  RegisterFile rf;
  Memory mem;
  Addr pc;
};
}
