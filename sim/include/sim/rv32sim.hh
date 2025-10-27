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

#include "memory.hh"
#include "register_file.hh"
#include "sim/instructions_registry.hh"

#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/spdlog.h"

namespace rv32 {

class Simulator final {
 public:
  Simulator(const std::vector<std::string>& cmd);
  void run();

  class RVException : public std::runtime_error {
   public:
    RVException(std::string_view what, Addr pc)
        : std::runtime_error(std::format("{} at pc = {}", what, pc)) {}
  };

  class IllegalInstruction : public RVException {
   public:
    IllegalInstruction(Addr pc) : RVException("Illegal instruction", pc) {}
  };

 private:
  SimulatorState state_;
  InstructionsRegistry instructions_registry_;
  std::shared_ptr<spdlog::logger> logger_;

  void loadElf(const std::filesystem::path& path);
  void createExecutionEnvironment(const std::vector<std::string>& cmd);
};
}  // namespace rv32
