@echo off

set GLFW_root_dir=..\lib\glfw
set GLFW_build_dir=..\lib\glfw\build
set GLAD_root_dir=..\lib\glad
set GLAD_build_dir=..\lib\glad\build

echo Installing GLFW!

:: x64 build
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF %GLFW_root_dir% -A x64 -B %GLFW_build_dir%\x64
cmake --build %GLFW_build_dir%\x64 --config Release --clean-first

:: Win32 build
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF %GLFW_root_dir% -A Win32 -B %GLFW_build_dir%\Win32
cmake --build %GLFW_build_dir%\Win32 --config Release --clean-first

echo Installing GLAD!

:: x64 build
cmake %GLAD_root_dir% -B %GLAD_build_dir%\x64 -A x64
cmake --build %GLAD_build_dir%\x64 --config Release --clean-first"

:: Win32 build
cmake %GLAD_root_dir% -B %GLAD_build_dir%\Win32 -A Win32
cmake --build %GLAD_build_dir%\Win32 --config Release --clean-first