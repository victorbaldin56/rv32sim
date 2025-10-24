add_executable(rv32sim main.cc)
target_link_libraries(rv32sim PRIVATE boost::boost sim)
target_compile_features(rv32sim PRIVATE cxx_std_17)
