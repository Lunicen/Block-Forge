@echo off

set build_dir=.\lib\glfw\build

:: Remove previous setup if exists
echo Removing previous build if exists
if exist %build_dir% del %build_dir%\*.* /s /q > nul 2>&1
if exist %build_dir% rmdir %build_dir% /s /q > nul 2>&1

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
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF .\lib\glfw -B %build_dir%
start "Debug build" cmd /c "cmake --build %build_dir% --config Debug"
start "Release build" cmd /c "cmake --build %build_dir% --config Release"
