export CC="clang"
export CXX="clang++"
export CMAKE_GENERATOR="Unix Makefiles"

cmake -S . -B build
cmake --build build -j 4
