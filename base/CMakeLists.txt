add_library(base mmaped_file.cc)

target_link_libraries(base PUBLIC boost::boost)
target_link_libraries(base PUBLIC spdlog::spdlog)
target_link_libraries(base PUBLIC magic_enum::magic_enum)
target_include_directories(base PUBLIC include)
target_compile_features(base PUBLIC cxx_std_20)
