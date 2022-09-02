@echo off

set FastNoiseTwo_root_dir=..\lib\FastNoise2
set FastNoiseTwo_build_dir=..\lib\FastNoise2\build

echo Installing FastNoise2!

:: x64 build
cmake -DFASTNOISE2_TESTS=OFF -DFASTNOISE2_NOISETOOL=OFF %FastNoiseTwo_root_dir% -A x64 -B %FastNoiseTwo_build_dir%\x64
cmake --build %FastNoiseTwo_build_dir%\x64 --config Debug --clean-first
cmake --build %FastNoiseTwo_build_dir%\x64 --config Release --clean-first

:: Win32 build
cmake -DFASTNOISE2_TESTS=OFF -DFASTNOISE2_NOISETOOL=OFF %FastNoiseTwo_root_dir% -A Win32 -B %FastNoiseTwo_build_dir%\Win32
cmake --build %FastNoiseTwo_build_dir%\Win32 --config Debug --clean-first
cmake --build %FastNoiseTwo_build_dir%\Win32 --config Release --clean-first