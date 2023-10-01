@echo off

cd ..

:: Target architectures
set "build_arch=x64"
set "build_type=Debug"

:: Library builds directory
set "tmp_build=tmp_build_win_x64_dbg"

:: Libraries
set "std_libraries=FastNoise2 glfw"
set "libraries=FastNoise2 glad glfw"

:: Cleanup and setup environment
for %%i in (%libraries%) do (
  if exist ".\lib\%%i\build\%build_arch%\%build_type%" (
    echo Cleaned %%i!
    rmdir ".\lib\%%i\build\%build_arch%\%build_type%" /s /q > nul 2>&1
  )
  
  mkdir ".\lib\%%i\build\%build_arch%\%build_type%"
  
  if exist ".\lib\%%i\%tmp_build%\" (
	rmdir ".\lib\%%i\%tmp_build%" /s /q > nul 2>&1
  )
)

set /a jobs=%NUMBER_OF_PROCESSORS%+1

:: Setup Ninja
set "ninja_path=%cd%\lib\ninja\build\Release\ninja.exe"
if not exist ".\lib\ninja\build" (
  cmake -S .\lib\ninja -B .\lib\ninja\build
  cmake --build .\lib\ninja\build --config Release --clean-first --parallel %jobs%
)

:: Build
:: FastNoise2
cmake -G Ninja -DCMAKE_MAKE_PROGRAM="%ninja_path%" -DCMAKE_BUILD_TYPE=%build_type% -DFASTNOISE2_TESTS=OFF -DFASTNOISE2_NOISETOOL=OFF -S .\lib\FastNoise2 -B .\lib\FastNoise2\%tmp_build%\%build_arch%

:: glfw
cmake -G Ninja -DCMAKE_MAKE_PROGRAM="%ninja_path%" -DCMAKE_BUILD_TYPE=%build_type% -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S .\lib\glfw -B .\lib\glfw\%tmp_build%\%build_arch%

:: glad
cmake -G Ninja -DCMAKE_MAKE_PROGRAM="%ninja_path%" -DCMAKE_BUILD_TYPE=%build_type% -DGLAD_API="gl=3.3" -S .\lib\glad -B .\lib\glad\%tmp_build%\%build_arch%

Rem Unfortunately this process cannot be ideally automated
Rem due the fact that there is no standard in building libraries

:: standard libraries (defined)
echo Building libraries
for %%k in (%std_libraries%) do (
	cmake --build .\lib\%%k\%tmp_build%\%build_arch% --config %build_type% --clean-first --parallel %jobs%
	mkdir ".\lib\%%k\build\%build_arch%\%build_type%"
	for /f %%f in ('dir /s /b ".\lib\%%k\%tmp_build%\%build_arch%\src\*.lib"') do (
		move %%~ff ".\lib\%%k\build\%build_arch%\%build_type%"
	)
	if "%build_type%"=="Debug" (
		for /f %%f in ('dir /s /b ".\lib\%%k\%tmp_build%\%build_arch%\*.pdb"') do (
			move %%~ff ".\lib\%%k\build\%build_arch%\%build_type%"
		)
	)
)

:: custom libraries
echo Building libraries requiring custom config

:: glad =======================================================================================
cmake --build .\lib\glad\%tmp_build%\%build_arch% --config %build_type% --clean-first --parallel %jobs%
mkdir ".\lib\glad\build\%build_arch%\%build_type%"
for /f %%f in ('dir /s /b ".\lib\glad\%tmp_build%\%build_arch%\*.lib"') do (
	move %%~ff ".\lib\glad\build\%build_arch%\%build_type%"
)
if "%build_type%"=="Debug" (
	for /f %%f in ('dir /s /b ".\lib\glad\%tmp_build%\%build_arch%\*.pdb"') do (
		move %%~ff ".\lib\glad\build\%build_arch%\%build_type%"
	)
)
move ".\lib\glad\%tmp_build%\%build_arch%\include" ".\lib\glad\build\%build_arch%\%build_type%"
move ".\lib\glad\%tmp_build%\%build_arch%\src\glad.c" ".\lib\glad\build\%build_arch%\%build_type%"

rmdir ".\lib\glad\%tmp_build%\%build_arch%" /s /q > nul 2>&1

:: Cleanup
for %%i in (%libraries%) do (
	if exist ".\lib\%%i\%tmp_build%" (
		rmdir ".\lib\%%i\%tmp_build%" /s /q > nul 2>&1
	)
)

cd scripts