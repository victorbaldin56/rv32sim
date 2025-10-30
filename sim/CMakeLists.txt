add_library(sim
  rv32sim.cc
  elfloader.cc
  instructions_registry.cc
)

target_link_libraries(sim PUBLIC boost::boost)
target_link_libraries(sim PUBLIC spdlog::spdlog)
target_link_libraries(sim PUBLIC base)
target_include_directories(sim PUBLIC include)
target_compile_features(sim PUBLIC cxx_std_20)
