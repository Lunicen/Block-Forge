@echo off

set root_dir=.\lib\glad
set output_dir=.\lib\glad\build

:: Remove previous setup if exists
echo Removing previous build if exists
if exist %output_dir% del %output_dir%\Win32\*.* /s /q > nul 2>&1
if exist %output_dir% rmdir %output_dir%\Win32 /s /q > nul 2>&1
if exist %output_dir% del %output_dir%\x64\*.* /s /q > nul 2>&1
if exist %output_dir% rmdir %output_dir%\x64 /s /q > nul 2>&1

:: Check if the library is downloaded
for /F %%i in ('dir /b /a "lib\glad"') do (
    echo GLAD is installed!
    goto :gladExists
)

:: Install missing dependencies
echo GLAD dependency is not installed! Downloading...
git pull --recurse-submodules

:gladExists
:: x64 build
echo Running cmake...
cmake -S%root_dir% -B%output_dir%\x64 -A x64
start "Debug build x64" cmd /c "cmake --build %output_dir%\x64 --config Debug --clean-first"
start "Release build x64" cmd /c "cmake --build %output_dir%\x64 --config Release --clean-first"

:: Win32 build
cmake -S%root_dir% -B%output_dir%\Win32 -A Win32
start "Debug build Win32" cmd /c "cmake --build %output_dir%\Win32 --config Debug --clean-first"
start "Release build Win32" cmd /c "cmake --build %output_dir%\Win32 --config Release --clean-first"