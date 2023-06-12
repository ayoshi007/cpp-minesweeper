add_executable(cpp_ms main.cpp)
target_compile_features(cpp_ms
    PRIVATE cxx_std_11
)
target_include_directories(cpp_ms
    PRIVATE src
)
target_link_libraries(cpp_ms
    PRIVATE my_minesweeper_obj
)