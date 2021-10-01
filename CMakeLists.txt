cmake_minimum_required(VERSION 3.16.4)

project(stack
        VERSION 0.0.0.0
        LANGUAGES CXX
        )

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options(-Werror -Wall -Wextra -Wpedantic -Wshadow)
set(CMAKE_CXX_CLANG_TIDY
    clang-tidy;
    --format-style=file;
    --header-filter=.;
    )

file(GLOB_RECURSE ALL_SOURCE_FILES *.cpp *.h)

add_custom_target(
    clang-format-stack
    COMMAND clang-format
    -i
    --sort-includes
    -style=file
    ${ALL_SOURCE_FILES}
)

add_subdirectory(stack)
