# rv32sim

A simple RISC-V 32-Bit simulator.
[![CI](https://github.com/victorbaldin56/rv32sim/actions/workflows/main.yml/badge.svg)](https://github.com/victorbaldin56/rv32sim/actions/workflows/main.yml)

## Overview

rv32sim (RISC-V 32-Bit simulator) is a functional RISC-V 32-Bit simulator
that can currently run RISC-V generic Linux code in ELF format.

## Features

### Supported extensions

rv32sim currently supports the following RISC-V extensions:

* I - base integer
* M - integer multiplication/division
* F - single-precision floating point operations
* Zbb - basic bit manipulation

### System calls

Currently these Linux system calls are supported:

* `read`
* `write`
* `exit`

### Requirements for executable file

Supported executable format is positional dependent ELF32. Here is
the list of requirements for input file (see [elf(5)](https://manpages.ubuntu.com/manpages/noble/en/man5/elf.5.html)
for ELF documentation).

| ELF Property | Value |
| --- | -- |
| Class | 32 bit |
| Endianness | Little Endian |
| OS ABI | System-V |
| Type | Executable file |
| Machine | RISC-V |

To create such ELF use a special GNU toolchain build `riscv64-unknown-elf-*`.

>[!NOTE]
> Toolchain is provided in Docker image, see [Docker](#with-docker).

To build a test program from source called `test.c`, see [tests](tests/riscv-interpreter-task/) submodule and its
[Makefile](tests/riscv-interpreter-task/Makefile).

## Building

It is highly recommended to use pre-built Docker image.

### With Docker

1. Clone the repo.

```sh
git clone https://github.com/victorbaldin56/rv32sim.git
```

Unless you need external submodule with tests from [@iDang3r](https://gitlab.com/iDang3r/),
you don't have to care about submodules here. If you really want to get tests too then

```sh
git submodule update --init --recursive
```

1. Pull the pre-built Docker image and start the Docker container using it. Recommended command:

```sh
docker run --restart unless-stopped -it -v [YOUR_BACKUP_VOLUME_PATH]:/home/dev --name linux_dev victorbaldin56/linux_dev:a51a343886c34b73ddf5344e72ce095c416af046
```

1. Install additional project dependencies with Conan

```sh
conan profile detect --force
conan install . --build=missing --output-folder=build -pr:a=conan_profiles/release
```

1. Configure the build

```sh
cmake --preset conan-release
```

1. Build

```sh
cmake --build build -j
```

### Have no Docker yet?

> [!TIP]
> It will be probably easier for you to install Docker because some tool
> requirements are specific.

You can check my [Dockerfile](https://github.com/victorbaldin56/DockerLinuxDev/blob/a51a343886c34b73ddf5344e72ce095c416af046/Dockerfile)
and build the same environment yourself.

## Usage

To get quick help on available commands, run:

```sh
./build/main/rv32im --help
```

To run a sample RISC-V 32-Bit program use:

```sh
./build/main/rv32sim -- ./[PROGRAM] [PROGRAM_ARGS]
```

> [!IMPORTANT]
> See [requirements](#requirements-for-executable-file) for input file.

## Unimplemented

These instructions from [supported extensions](#supported-extensions) are currently unimplemented:

* `ebreak`
* `fence`

## License

This project is licensed after APACHE 2.0 license.

## Contribution

This project is currently in active development. If you wish to contribute
you are welcome to submit pull requests and issues. Thank you!
