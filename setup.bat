@echo off

:: Target architectures
set "build_types=Win32 x64"

:: Libraries
set "libraries=FastNoise2 glad glfw"

:: Remove previous setup if exists
for %%i in (%libraries%) do (
  if exist ".\lib\%%i\build\" (
    echo Cleaned %%i!
    rmdir ".\lib\%%i\build\" /s /q > nul 2>&1
  )
)

echo Updating submodules...
git submodule update --init --recursive
git pull --recurse-submodules

set /a jobs=%NUMBER_OF_PROCESSORS%+1
for %%i in (%build_types%) do (

	:: FastNoise2
	cmake -DFASTNOISE2_TESTS=OFF -DFASTNOISE2_NOISETOOL=OFF -S .\lib\FastNoise2 -B .\lib\FastNoise2\build\%%i

	:: glad
	cmake -DGLAD_API="gl=3.3" -S .\lib\glad -B .\lib\glad\build\%%i -A %%i

	:: glfw
	cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S .\lib\glfw -B .\lib\glfw\build\%%i -A %%i
)

Rem Unfortunately this process cannot be ideally automated
Rem due the fact that there is no standard in building libraries

:: standard libraries (defined)
echo Building libraries
set "std_libraries=FastNoise2 glfw"

for %%i in (%std_libraries%) do (
	for %%j in (%build_types%) do (

		cmake --build .\lib\%%i\build\%%j --config Debug --clean-first --parallel %jobs%
		mkdir ".\lib\%%i\build\Debug"
		for /f %%f in ('dir /s /b ".\lib\%%i\build\%%j\*.lib"') do (
			move %%~ff ".\lib\%%i\build\Debug"
		)
		for /f %%f in ('dir /s /b ".\lib\%%i\build\%%j\*.pdb"') do (
			move %%~ff ".\lib\%%i\build\Debug"
		)
		
		cmake --build .\lib\%%i\build\%%j --config Release --clean-first --parallel %jobs%
		mkdir ".\lib\%%i\build\Release"
		for /f %%f in ('dir /s /b ".\lib\%%i\build\%%j\*.lib"') do (
			move %%~ff ".\lib\%%i\build\Release"
		)
		
		rmdir ".\lib\%%i\build\%%j" /s /q > nul 2>&1
		mkdir ".\lib\%%i\build\%%j"
		move ".\lib\%%i\build\Debug" ".\lib\%%i\build\%%j"
		move ".\lib\%%i\build\Release" ".\lib\%%i\build\%%j"
	)
)

:: custom libraries
echo Building libraries requiring custom config
for %%i in (%build_types%) do (

	:: glad =======================================================================================
	cmake --build .\lib\glad\build\%%i --config Debug --clean-first --parallel %jobs%
	mkdir ".\lib\glad\build\Debug"
	for /f %%f in ('dir /s /b ".\lib\glad\build\%%i\*.lib"') do (
		move %%~ff ".\lib\glad\build\Debug"
	)
	for /f %%f in ('dir /s /b ".\lib\glad\build\%%i\*.pdb"') do (
		move %%~ff ".\lib\glad\build\Debug"
	)
	move ".\lib\glad\build\%%i\include" ".\lib\glad\build\Debug"
	
	cmake --build .\lib\glad\build\%%i --config Release --clean-first --parallel %jobs%
	mkdir ".\lib\glad\build\Release"
	for /f %%f in ('dir /s /b ".\lib\glad\build\%%i\*.lib"') do (
		move %%~ff ".\lib\glad\build\Release"
	)
	move ".\lib\glad\build\%%i\include" ".\lib\glad\build\Release"

	move ".\lib\glad\build\%%i\src\glad.c" ".\lib\glad\build"
	
	rmdir ".\lib\glad\build\%%i" /s /q > nul 2>&1
	mkdir ".\lib\glad\build\%%i"
	move ".\lib\glad\build\Debug" ".\lib\glad\build\%%i"
	move ".\lib\glad\build\Release" ".\lib\glad\build\%%i"
)
