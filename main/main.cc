// See LICENSE for license details.

// rv32sim - a simple rv32 simulator
//
// Main function.

#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>

#include "boost/program_options.hpp"
#include "sim/rv32sim.hh"

namespace po = boost::program_options;

namespace {

void help(char** argv, const po::options_description& desc) {
  std::cout << "Usage: " << argv[0] << " ./user-binary [user-binary-options]\n";
  std::cout << desc << std::endl;
}

std::vector<std::string> splitCommas(std::string_view sv,
                                     bool keep_empty = false) {
  const std::size_t comma_count =
      static_cast<std::size_t>(std::count(sv.begin(), sv.end(), ','));
  const std::size_t token_count = comma_count + 1;

  std::vector<std::string> out;
  out.reserve(token_count);

  std::size_t start = 0;
  std::generate_n(std::back_inserter(out), token_count, [&]() -> std::string {
    if (start > sv.size()) {
      return std::string();
    }
    auto pos = sv.find(',', start);
    if (pos == std::string_view::npos) {
      const std::size_t len = sv.size() - start;
      std::string token(sv.substr(start, len));
      start = sv.size() + 1;  // mark done
      return token;
    } else {
      const std::size_t len = pos - start;
      std::string token{sv.substr(start, len)};
      start = pos + 1;
      return token;
    }
  });

  if (!keep_empty) {
    std::erase_if(out, [](auto const& s) { return s.empty(); });
  }

  return out;
}
}  // namespace

int main(int argc, char** argv) try {
  po::options_description desc("Options");
  // clang-format off
  desc.add_options()
    ("help,h", "Print help message and exit")
    ("trace", po::value<std::string>(),
              "Enable trace messages, see available tracers")
    ("args", po::value<std::vector<std::string>>()->multitoken(),
             "User command line to execute: --args <program> [args...]");
  // clang-format on

  po::positional_options_description p;
  p.add("args", -1);  // --args can be omitted

  po::variables_map vm;
  po::command_line_parser cmdp(argc, argv);
  try {
    po::store(cmdp.options(desc).positional(p).run(), vm);
  } catch (po::error& e) {
    std::cerr << e.what() << std::endl;
    help(argv, desc);
    return EXIT_FAILURE;
  }

  if (argc == 1 || vm.count("help")) {
    help(argv, desc);
    return 0;
  }

  if (vm.count("args")) {
    auto simulator_logger = spdlog::stderr_color_mt("Simulator");
    auto elf_loader_logger = spdlog::stderr_color_mt("ElfLoader");

    // use global registry to access all loggers
    if (vm.count("trace")) {
      auto logger_names = splitCommas(vm["trace"].as<std::string>());
      std::for_each(
          logger_names.begin(), logger_names.end(), [](const auto& name) {
            spdlog::get(name)->set_level(spdlog::level::level_enum::trace);
          });
    }

    auto cmd = vm["args"].as<std::vector<std::string>>();
    rv32::Simulator sim(cmd);

    try {
      sim.run();
    } catch (rv32::Simulator::Exception& e) {
      sim.getLogger()->error("{}", e.what());
      return EXIT_FAILURE;
    }
    return sim.getExitCode();
  }

  return 0;
} catch (std::exception& e) {
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
}
