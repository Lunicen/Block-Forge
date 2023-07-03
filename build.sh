#!/bin/bash

# Library builds directory
tmp_build="tmp_unix"

# Libraries
std_libraries="FastNoise2 glfw"
libraries="FastNoise2 glad glfw"

# Cleanup and setup environment
for library in $libraries; do
  if [ -d "./lib/$library/build/Unix" ]; then
    echo "Cleaned $library!"
    rm -rf "./lib/$library/build/Unix" > /dev/null 2>&1
  fi
  
  mkdir -p "./lib/$library/build/Unix"
  
  if [ -d "./lib/$library/$tmp_build" ]; then
    rm -rf "./lib/$library/$tmp_build" > /dev/null 2>&1
  fi
done

jobs=$((NUMBER_OF_PROCESSORS + 1))

# Build
# FastNoise2
cmake -G Ninja -DFASTNOISE2_TESTS=OFF -DFASTNOISE2_NOISETOOL=OFF -S ./lib/FastNoise2 -B ./lib/FastNoise2/$tmp_build

# glfw
cmake -G Ninja -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S ./lib/glfw -B ./lib/glfw/$tmp_build

# glad
cmake -G Ninja -DGLAD_API="gl=3.3" -S ./lib/glad -B ./lib/glad/$tmp_build

# standard libraries (defined)
echo "Building libraries"
for std_lib in $std_libraries; do
  ninja -C "./lib/$std_lib/$tmp_build"
  mkdir -p "./lib/$std_lib/build/Unix/Release"
  find "./lib/$std_lib/$tmp_build/src" -name "*.a" -exec mv {} "./lib/$std_lib/build/Unix/Release" \;
done

# custom libraries
echo "Building libraries requiring custom config"

# glad
ninja -C "./lib/glad/$tmp_build"
mkdir -p "./lib/glad/build/Unix/Release"
find "./lib/glad/$tmp_build" -name "*.a" -exec mv {} "./lib/glad/build/Unix/Release" \;

mv "./lib/glad/$tmp_build/include" "./lib/glad/build/Unix/Release"
mv "./lib/glad/$tmp_build/src/glad.c" "./lib/glad/build/Unix/Release"

rm -rf "./lib/glad/$tmp_build" > /dev/null 2>&1

# Cleanup
for library in $libraries; do
  if [ -d "./lib/$library/$tmp_build" ]; then
    rm -rf "./lib/$library/$tmp_build" > /dev/null 2>&1
  fi
done

if [ -d "./build" ]; then
  rm -rf "./build" > /dev/null 2>&1
fi

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -S . -B build
ninja -C "./build"