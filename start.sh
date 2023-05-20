cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=vcpkg/scripts/buildsystems/vcpkg.cmake
cd build && cmake --build .
# cp app/cpp-ms ../cpp-ms