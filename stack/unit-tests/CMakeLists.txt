enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

add_executable(stack-unit-tests
               StackTest.cpp
               )
target_compile_options(stack-unit-tests PRIVATE
                       -fsanitize=address
                       -fsanitize-address-use-after-scope
                       -fno-omit-frame-pointer
                       -fno-optimize-sibling-calls
                       -g
                       -O1
                       )
target_link_options(stack-unit-tests PRIVATE
                    -fsanitize=address
                    )
target_link_libraries(stack-unit-tests
                      stack
                      GTest::Main
                      )
gtest_discover_tests(stack-unit-tests)
