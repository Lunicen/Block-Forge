#!/bin/bash

# Target architectures
build_types=("x86_64" "amd64")

# Libraries
libraries=("FastNoise2" "glad" "glfw")

# Remove previous setup if exists
for i in "${libraries[@]}"; do
  if [ -d "./lib/$i/build/" ]; then
    echo "Cleaned $i!"
    rm -rf "./lib/$i/build/"
  fi
done

echo "Updating submodules..."
git submodule update --init --recursive
git pull --recurse-submodules

jobs=$(( $(nproc) + 1 ))

for i in "${build_types[@]}"; do
  # FastNoise2
  cmake -DFASTNOISE2_TESTS=OFF -DFASTNOISE2_NOISETOOL=OFF -S ./lib/FastNoise2 -B ./lib/FastNoise2/build/$i -A $i
  
  # glad
  cmake -DGLAD_API="gl=3.3" -S ./lib/glad -B ./lib/glad/build/$i -A $i
  
  # glfw
  cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S ./lib/glfw -B ./lib/glfw/build/$i -A $i
done

# Standard libraries (defined)
echo "Building libraries"
std_libraries=("FastNoise2" "glfw")

for i in "${std_libraries[@]}"; do
  for j in "${build_types[@]}"; do
    cmake --build ./lib/$i/build/$j --config Debug --clean-first --parallel $jobs
    mkdir "./lib/$i/build/Debug"
    find "./lib/$i/build/$j/" -name "*.lib" -exec mv {} "./lib/$i/build/Debug" \;
    find "./lib/$i/build/$j/" -name "*.pdb" -exec mv {} "./lib/$i/build/Debug" \;
    
    cmake --build ./lib/$i/build/$j --config Release --clean-first --parallel $jobs
    mkdir "./lib/$i/build/Release"
    find "./lib/$i/build/$j/" -name "*.lib" -exec mv {} "./lib/$i/build/Release" \;
    
    rm -rf "./lib/$i/build/$j"
    mkdir "./lib/$i/build/$j"
    mv "./lib/$i/build/Debug" "./lib/$i/build/$j"
    mv "./lib/$i/build/Release" "./lib/$i/build/$j"
  done
done

# Custom libraries
echo "Building libraries requiring custom config"

for i in "${build_types[@]}"; do
  # glad
  cmake --build ./lib/glad/build/$i --config Debug --clean-first --parallel $jobs
  mkdir "./lib/glad/build/Debug"
  find "./lib/glad/build/$i/" -name "*.lib" -exec mv {} "./lib/glad/build/Debug" \;
  find "./lib/glad/build/$i/" -name "*.pdb" -exec mv {} "./lib/glad/build/Debug" \;
  mv "./lib/glad/build/$i/include" "./lib/glad/build/Debug"
  
  cmake --build ./lib/glad/build/$i --config Release --clean-first --parallel $jobs
  mkdir "./lib/glad/build/Release"
  find "./lib/glad/build/$i/" -name "*.lib" -exec mv {} "./lib/glad/build/Release" \;
  mv "./lib/glad/build/$i/include" "./lib/glad/build/Release"

  mv "./lib/glad/build/$i/src/glad.c" "./lib/glad/build"
  
  rm -rf "./lib/glad/build/$i"
  mkdir "./lib/glad/build/$i"
  mv "./lib/glad/build/Debug" "./lib/glad/build/$i"
  mv "./lib/glad/build/Release" "./lib/glad/build/$i"
done
