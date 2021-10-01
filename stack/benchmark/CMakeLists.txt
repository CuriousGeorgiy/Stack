find_package(benchmark REQUIRED)

add_executable(stack-growth-coeff-benchmark
               StackGrowthCoeffBenchmark.cpp
               )
target_link_libraries(stack-growth-coeff-benchmark
                      stack
                      benchmark::benchmark
                      benchmark::benchmark_main
                      )
