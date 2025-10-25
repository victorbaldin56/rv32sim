// See LICENSE for license details.

// rv32sim - a simple RV32 simulator
//
// Simulator class.

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "cpu.hh"
#include "memory.hh"

namespace RV32 {

class Simulator final {
 public:
  Simulator(const std::vector<std::string>& cmd);
  void run();

 private:
  CPU cpu_;
  Memory mem_;

  void loadElf(const std::filesystem::path& path);
  void createExecutionEnvironment(const std::vector<std::string>& cmd);
};
}
