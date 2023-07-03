@echo off

cd ..

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
:: Update and init github submodules
echo Updating submodules...
git submodule update --init --recursive
git pull --recurse-submodules

cd scripts

:: Build x86
call "%vsvars_location%\vcvars32.bat"
call "win_x86_dbg.bat"
call "win_x86.bat"

:: Build x64
call "%vsvars_location%\vcvars64.bat"
call "win_x64_dbg.bat"
call "win_x64.bat"