@echo off

:: Target architectures
set "build_types=Win32 x64"

:: Libraries
set "libraries=glfw glad FastNoise2"

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

	:: glfw
	cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -S .\lib\glfw -A %%i -B .\lib\glfw\build\%%i
	start "GLFW Debug build %%i" cmd /c "cmake --build .\lib\glfw\build\%%i --config Debug --clean-first --parallel %jobs%"
	start "GLFW Release build %%i" cmd /c "cmake --build .\lib\glfw\build\%%i --config Release --clean-first --parallel %jobs%"
	
	:: glad
	cmake -S .\lib\glad -B .\lib\glad\build\%%i -A %%i
	start "GLAD Debug build %%i" cmd /c "cmake --build .\lib\glad\build\%%i --config Debug --clean-first --parallel %jobs%"
	start "GLAD Release build %%i" cmd /c "cmake --build .\lib\glad\build\%%i --config Release --clean-first --parallel %jobs%"

	:: FastNoise2
	cmake -DFASTNOISE2_TESTS=OFF -DFASTNOISE2_NOISETOOL=OFF .\lib\FastNoise2 -A %%i -B .\lib\FastNoise2\build\%%i
	start "FastNoise2 Debug build %%i" cmd /c "cmake --build .\lib\FastNoise2\build\%%i --config Debug --clean-first --parallel %jobs%"
	start "FastNoise2 Release build %%i" cmd /c "cmake --build .\lib\FastNoise2\build\%%i --config Release --clean-first --parallel %jobs%"
	
)