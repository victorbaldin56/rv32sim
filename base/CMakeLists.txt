add_library(base scoped_mmap.cc)
target_include_directories(base PUBLIC include)
target_compile_features(base PUBLIC cxx_std_20)
