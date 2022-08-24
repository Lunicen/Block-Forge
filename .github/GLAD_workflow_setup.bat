@echo off

set GLAD_root_dir=..\lib\glad
set GLAD_build_dir=..\lib\glad\build

echo Installing GLAD!

:: x64 build
cmake %GLAD_root_dir% -B %GLAD_build_dir%\x64 -A x64
cmake --build %GLAD_build_dir%\x64 --config Debug --clean-first
cmake --build %GLAD_build_dir%\x64 --config Release --clean-first"

:: Win32 build
cmake %GLAD_root_dir% -B %GLAD_build_dir%\Win32 -A Win32
cmake --build %GLAD_build_dir%\Win32 --config Debug --clean-first
cmake --build %GLAD_build_dir%\Win32 --config Release --clean-first