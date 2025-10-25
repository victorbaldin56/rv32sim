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

int main(int argc, char** argv) try {
  po::options_description desc("Options");
  // clang-format off
  desc.add_options()
    ("help,h", "Print help message and exit")
    ("args", po::value<std::vector<std::string>>()->multitoken(),
             "User command line to execute: --args <program> [args...]");
  // clang-format on

  po::positional_options_description p;
  p.add("args", -1);  // --args can be omitted

  po::variables_map vm;
  po::command_line_parser cmdp(argc, argv);
  po::store(cmdp.options(desc).positional(p).run(), vm);

  if (vm.count("help")) {
    std::cout << "Usage: " << argv[0]
              << " ./user-binary [user-binary-options]\n";
    std::cout << desc << std::endl;
    return 0;
  }

  if (vm.count("args")) {
    auto cmd = vm["args"].as<std::vector<std::string>>();
    rv32::Simulator sim(cmd);
    sim.run();
  }

  return 0;
} catch (std::exception& e) {
  std::cerr << e.what() << std::endl;
  return EXIT_FAILURE;
}
