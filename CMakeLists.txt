cmake_minimum_required(VERSION 3.8)
project(pdp11)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES src/main.cpp src/cpu/cpu.cpp src/cpu/cpu.h src/cpu/decoder/decoder.cpp src/cpu/decoder/decoder.h src/emulator/emulator.cpp src/emulator/emulator.h src/memory/memory.cpp src/memory/memory.h src/cpu/instruction/instruction.cpp src/cpu/instruction/instruction.h)
add_executable(pdp11 ${SOURCE_FILES})

