add_executable(test_ms test.cpp)
target_compile_features(test_ms PRIVATE cxx_std_11)
target_link_libraries(test_ms PRIVATE my_minesweeper)