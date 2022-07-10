@echo off

set build_dir=.\lib\glfw\build

:: Remove previous setup if exists
echo Removing previous build if exists
if exist %build_dir% del %build_dir%_Win32\*.* /s /q > nul 2>&1
if exist %build_dir% rmdir %build_dir%_Win32 /s /q > nul 2>&1
if exist %build_dir% del %build_dir%_x64\*.* /s /q > nul 2>&1
if exist %build_dir% rmdir %build_dir%_x64 /s /q > nul 2>&1

:: Check if the library is downloaded
for /F %%i in ('dir /b /a "lib\glfw*"') do (
    echo GLFW is installed!
    goto :glfwExists
)

:: Install missing dependencies
echo GLFW dependency is not installed! Downloading...
git submodule update --init --recursive

:glfwExists
echo Running cmake...
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF .\lib\glfw -A x64 -B %build_dir%_x64
start "Debug build x64" cmd /c "cmake --build %build_dir%_x64 --config Debug"
start "Release build x64" cmd /c "cmake --build %build_dir%_x64 --config Release"

cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF .\lib\glfw -A Win32 -B %build_dir%_Win32
start "Debug build Win32" cmd /c "cmake --build %build_dir%_Win32 --config Debug"
start "Release build Win32" cmd /c "cmake --build %build_dir%_Win32 --config Release"