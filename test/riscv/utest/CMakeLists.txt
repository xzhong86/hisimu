
file(GLOB srcs *.cc)

add_executable(riscv-utest ${srcs})

target_link_libraries(riscv-utest riscv)
