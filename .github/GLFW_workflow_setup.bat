@echo off

set GLFW_root_dir=..\lib\glfw
set GLFW_build_dir=..\lib\glfw\build

echo Installing GLFW!

:: x64 build
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF %GLFW_root_dir% -A x64 -B %GLFW_build_dir%\x64
cmake --build %GLFW_build_dir%\x64 --config Debug --clean-first
cmake --build %GLFW_build_dir%\x64 --config Release --clean-first

:: Win32 build
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF %GLFW_root_dir% -A Win32 -B %GLFW_build_dir%\Win32
cmake --build %GLFW_build_dir%\Win32 --config Debug --clean-first
cmake --build %GLFW_build_dir%\Win32 --config Release --clean-first