@echo off

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
cmake -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF .\lib\glfw