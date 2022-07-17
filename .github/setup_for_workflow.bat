@echo off

set GLFW_root_dir=..\lib\glfw
set GLFW_build_dir=..\lib\glfw\build
set GLAD_root_dir=..\lib\glad
set GLAD_build_dir=..\lib\glad\build

echo Installing GLFW!
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF %GLFW_root_dir% -A Win32 -B %GLFW_build_dir%\Win32
cmake --build %GLFW_build_dir%\Win32 --config Release --clean-first

echo Installing GLAD!
cmake %GLAD_root_dir% -B %GLAD_build_dir%\Win32 -A Win32
cmake --build %GLAD_build_dir%\Win32 --config Release --clean-first