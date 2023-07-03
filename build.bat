@echo off

:: Environment detection
:: Thanks to (https://renenyffenegger.ch/notes/Windows/development/Visual-Studio/environment-variables/index)
set "vs_installer=%programfiles(x86)%\Microsoft Visual Studio\Installer"

if not exist "%vs_installer%\vswhere.exe" (
    echo Cannot detect MS Visual Studio environment.
	echo "%vs_installer%\vswhere.exe"
	exit /b 2
) else (
	for /f "usebackq delims=" %%i in (`"%vs_installer%\vswhere" -latest -property installationPath`) do (
		set "vsvars_location=%%i\VC\Auxiliary\Build"
		goto :vsvars_found
	)
)

:vsvars_found
:: Determine architecture
for /f "usebackq skip=1 tokens=2 delims==" %%i in (`wmic OS get OSArchitecture /value`) do (
    set "arch=%%i"
    goto :architecture_checked
)

:architecture_checked
echo Detected %arch% architecture.

:: Update and init github submodules
echo Updating submodules...
git submodule update --init --recursive
git pull --recurse-submodules

:: Build libraries
if "%arch%"=="32-bit" (
    call "%vsvars_location%\vcvars32.bat"
	cd scripts
	call "win_x86.bat"
	cd ..
) else (
    call "%vsvars_location%\vcvars64.bat"
	cd scripts
	call "win_x64.bat"
	cd ..
)

:: Remove previous build is exists
if exist ".\build\" (
  echo Removed previous build!
  rmdir ".\build\" /s /q > nul 2>&1
)

:: Ninja
set /a jobs=%NUMBER_OF_PROCESSORS%+1
if not exist ".\lib\ninja\build" (
  cmake -S .\lib\ninja -B .\lib\ninja\build
  cmake --build .\lib\ninja\build --config Release --clean-first --parallel %jobs%
)

:: Final build
set "ninja_path=%cd%\lib\ninja\build\Release\ninja.exe"
cmake -G Ninja -DCMAKE_MAKE_PROGRAM="%ninja_path%" -DCMAKE_BUILD_TYPE=Release -DMSVC=true -S . -B build
cmake --build build --config Release --parallel %jobs%
