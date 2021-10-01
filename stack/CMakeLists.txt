add_library(stack INTERFACE)
target_include_directories(stack INTERFACE include)

add_subdirectory(benchmark)
add_subdirectory(unit-tests)
