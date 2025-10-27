add_library(base mmaped_file.cc)
target_link_libraries(base PUBLIC boost::boost)
target_include_directories(base PUBLIC include)
target_compile_features(base PUBLIC cxx_std_20)
