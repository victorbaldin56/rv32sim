include(default)

[settings]
compiler.cppstd=gnu20
build_type=Debug

[conf]
tools.build:cflags=["-fsanitize=address,leak,undefined"]
tools.build:cxxflags=["-fsanitize=address,leak,undefined"]
tools.build:exelinkflags=["-fsanitize=address,leak,undefined"]
tools.build:sharedlinkflags=["-fsanitize=address,leak,undefined"]
