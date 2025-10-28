// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Simulator class.

#pragma once

#include <filesystem>
#include <format>
#include <stdexcept>
#include <string>
#include <vector>

#include "base/logger.hh"
#include "memory.hh"
#include "register_file.hh"
#include "sim/instructions_registry.hh"

namespace rv32 {

class Simulator final {
 public:
  Simulator(const std::vector<std::string>& cmd);
  void run();

  auto getLogger() const noexcept { return logger_; }

  class RVException : public std::runtime_error {
   public:
    RVException(std::string_view what, Addr pc)
        : std::runtime_error(std::format("{} at pc = 0x{:x}", what, pc)) {}
  };

  class IllegalInstruction : public RVException {
   public:
    IllegalInstruction(RawInstruction raw, Addr pc)
        : RVException(std::format("Illegal instruction 0x{:x}", raw), pc) {}
  };

 private:
  SimulatorState state_;
  InstructionsRegistry instructions_registry_;
  std::shared_ptr<spdlog::logger> logger_;

  void loadElf(const std::filesystem::path& path);
  void createExecutionEnvironment(const std::vector<std::string>& cmd);
};
}  // namespace rv32
