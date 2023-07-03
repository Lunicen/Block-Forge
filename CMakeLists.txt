cmake_minimum_required (VERSION 3.15)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (BlockForge)

# Set proper configuration
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
  if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(ARCHITECTURE "Win32")
  elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE "x64")
  endif()
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
  set(ARCHITECTURE "Unix")
else()
  message(FATAL_ERROR 
	"This platform is unsupported! "
	"Please modify the CMakeLists.txt by adding the architecture config.")
endif()

if(NOT CMAKE_BUILD_TYPE)
  if(DEBUG_MODE)
    set(CMAKE_BUILD_TYPE "Debug")
  else()
    set(CMAKE_BUILD_TYPE "Release")
  endif()
endif()

# Add the common source files
file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Add the GLAD source file conditionally based on the system
list(APPEND SOURCE_FILES "${CMAKE_SOURCE_DIR}/lib/glad/build/${ARCHITECTURE}/${CMAKE_BUILD_TYPE}/glad.c")

# Add the ImGUI header files
list(APPEND SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.h"
    "${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.h"
    "${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3_loader.h"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imconfig.h"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui.h"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui_internal.h"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imstb_rectpack.h"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imstb_textedit.h"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imstb_truetype.h"
)

# Add the ImGUI source files
list(APPEND SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_glfw.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/backends/imgui_impl_opengl3.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui_demo.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui_draw.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui_tables.cpp"
    "${CMAKE_SOURCE_DIR}/lib/imgui/imgui_widgets.cpp"
)

add_executable (BlockForge ${SOURCE_FILES})
include_directories(BlockForge 
    PRIVATE 
    "${CMAKE_SOURCE_DIR}/include"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BlockForge PROPERTY CXX_STANDARD 20)
endif()

# Files to copy
set(to_copy
    "Settings.json"
    "data"
)

foreach(file ${to_copy})
    set(copy_src "${CMAKE_SOURCE_DIR}/${file}")
    set(copy_dst "${CMAKE_BINARY_DIR}/${file}")

    if(EXISTS ${copy_dst})
        file(REMOVE_RECURSE ${copy_dst})
    endif()

    file(COPY ${copy_src} DESTINATION ${CMAKE_BINARY_DIR})
endforeach()

option(DEBUG_MODE "Compile code in debug mode?" OFF)

# OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(OpenGL::GL)

# GLAD
find_library(glad_path NAMES glad PATHS "${CMAKE_SOURCE_DIR}/lib/glad/build/${ARCHITECTURE}/${CMAKE_BUILD_TYPE}")
target_link_libraries(${PROJECT_NAME} ${glad_path})
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/glad/build/${ARCHITECTURE}/${CMAKE_BUILD_TYPE}/include")
message("Added ${glad_path}")

# GLFW
find_library(glfw_path NAMES glfw3 PATHS "${CMAKE_SOURCE_DIR}/lib/glfw/build/${ARCHITECTURE}/${CMAKE_BUILD_TYPE}")
target_link_libraries(${PROJECT_NAME} ${glfw_path})
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/glfw/include")
message("Added ${glfw_path}")

# FastNoise2
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  find_library(fastnoise2_path NAMES "FastNoiseD" PATHS "${CMAKE_SOURCE_DIR}/lib/FastNoise2/build/${ARCHITECTURE}/${CMAKE_BUILD_TYPE}")
else()
  find_library(fastnoise2_path NAMES "FastNoise" PATHS "${CMAKE_SOURCE_DIR}/lib/FastNoise2/build/${ARCHITECTURE}/${CMAKE_BUILD_TYPE}")
endif()
target_link_libraries(${PROJECT_NAME} ${fastnoise2_path})
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/FastNoise2/include")
message("Added ${fastnoise2_path}")

if (MSVC)
  set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>DLL:Debug>")
  add_compile_definitions("/MP")
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(_ITERATOR_DEBUG_LEVEL=2)
    add_compile_definitions(_DEBUG=1)
  endif()
endif()

# imgui
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/imgui")

# JSON
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/json/include")

# GLM
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/glm")

# glText
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/glText")

# Robin Hood Hashing
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/robin-hood-hashing/src/include")

# spdlog
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/spdlog/include")

# SPSC Queue
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/SPSCQueue/include")

# stb
include_directories(PRIVATE "${CMAKE_SOURCE_DIR}/lib/stb")