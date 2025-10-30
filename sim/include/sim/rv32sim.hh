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
  int getExitCode() const noexcept {
    int exit_code = state_.rf.get(RegisterFile::Register::kA0);
    logger_->info("Program exited with code {}", exit_code);
    return exit_code;
  }

  class Exception : public std::runtime_error {
   public:
    Exception(std::string_view what, Addr pc)
        : std::runtime_error(std::format("{} at pc = 0x{:x}", what, pc)) {}
  };

  class IllegalInstruction : public Exception {
   public:
    IllegalInstruction(RawInstruction raw, Addr pc)
        : Exception(std::format("Illegal instruction 0x{:x}", raw), pc) {}
  };

 private:
  SimulatorState state_;
  InstructionsRegistry instructions_registry_;
  std::shared_ptr<spdlog::logger> logger_;

  void loadElf(const std::filesystem::path& path);
  void createExecutionEnvironment(const std::vector<std::string>& cmd);
  void throwException [[noreturn]] (ExecutionResult res);
};
}  // namespace rv32
