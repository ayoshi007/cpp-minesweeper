add_executable(cpp-ms main.cpp)
target_compile_features(cpp-ms PRIVATE cxx_std_11)
target_link_libraries(cpp-ms PRIVATE my_minesweeper)