cmake -B build -S .
cmake --build build
./build/hello
# cd build && ctest --output-on-failure
# cd ..