add_executable(cpp_ms main.cpp)
target_compile_features(cpp_ms PRIVATE cxx_std_11)
target_link_libraries(cpp_ms PRIVATE my_minesweeper)
target_compile_options(cpp_ms PRIVATE -Wall -Wextra -Wpedantic -Werror)