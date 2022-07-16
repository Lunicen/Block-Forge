@echo off

set GLFW_root_dir=.\lib\glfw
set GLFW_build_dir=.\lib\glfw\build
set GLAD_root_dir=.\lib\glad
set GLAD_build_dir=.\lib\glad\build

:: Remove previous setup if exists
echo Removing previous build if exists
if exist %GLFW_build_dir% del %GLFW_build_dir%\Win32\*.* /s /q > nul 2>&1
if exist %GLFW_build_dir% rmdir %GLFW_build_dir%\Win32 /s /q > nul 2>&1
if exist %GLFW_build_dir% del %GLFW_build_dir%\x64\*.* /s /q > nul 2>&1
if exist %GLFW_build_dir% rmdir %GLFW_build_dir%\x64 /s /q > nul 2>&1

if exist %GLAD_build_dir% del %GLAD_build_dir%\Win32\*.* /s /q > nul 2>&1
if exist %GLAD_build_dir% rmdir %GLAD_build_dir%\Win32 /s /q > nul 2>&1
if exist %GLAD_build_dir% del %GLAD_build_dir%\x64\*.* /s /q > nul 2>&1
if exist %GLAD_build_dir% rmdir %GLAD_build_dir%\x64 /s /q > nul 2>&1

:: Check if the library is downloaded
for /F %%i in ('dir /b /a "%GLFW_root_dir%\*"') do (
    echo GLFW is downloaded!
	goto :checkGLAD
)
echo GLFW module is missing!

:checkGLAD
for /F %%i in ('dir /b /a "%GLAD_root_dir%\*"') do (
    echo GLAD is downloaded!
    goto :allSubmodulesInstalled
)
echo GLAD module is missing!

:installMissingSubmodules
:: Install missing dependencies
echo Some modules are missing! Downloading...
git submodule update --init --recursive
git pull --recurse-submodules

:allSubmodulesInstalled
echo Installing GLFW!

:: x64 build
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF %GLFW_root_dir% -A x64 -B %GLFW_build_dir%\x64
start "GLFW Debug build x64" cmd /c "cmake --build %GLFW_build_dir%\x64 --config Debug --clean-first"
start "GLFW Release build x64" cmd /c "cmake --build %GLFW_build_dir%\x64 --config Release --clean-first"

:: Win32 build
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF %GLFW_root_dir% -A Win32 -B %GLFW_build_dir%\Win32
start "GLFW Debug build Win32" cmd /c "cmake --build %GLFW_build_dir%\Win32 --config Debug --clean-first"
start "GLFW Release build Win32" cmd /c "cmake --build %GLFW_build_dir%\Win32 --config Release --clean-first"

echo Installing GLAD!

:: x64 build
cmake %GLAD_root_dir% -B %GLAD_build_dir%\x64 -A x64
start "GLAD Debug build x64" cmd /c "cmake --build %GLAD_build_dir%\x64 --config Debug --clean-first"
start "GLAD Release build x64" cmd /c "cmake --build %GLAD_build_dir%\x64 --config Release --clean-first"

:: Win32 build
cmake %GLAD_root_dir% -B %GLAD_build_dir%\Win32 -A Win32
start "GLAD Debug build Win32" cmd /c "cmake --build %GLAD_build_dir%\Win32 --config Debug --clean-first"
start "GLAD Release build Win32" cmd /c "cmake --build %GLAD_build_dir%\Win32 --config Release --clean-first"