// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Simulator class.

#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "memory.hh"
#include "register_file.hh"

namespace rv32 {

class Simulator final {
 public:
  Simulator(const std::vector<std::string>& cmd);
  void run();

 private:
  RegisterFile rf_;
  Memory mem_;

  Addr pc_ = 0;

  void loadElf(const std::filesystem::path& path);
  void createExecutionEnvironment(const std::vector<std::string>& cmd);
};
}  // namespace rv32
