cmake_minimum_required (VERSION 3.17)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (BlockForge)

# Add source to this project's executable.
file(GLOB_RECURSE SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/src/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/Application/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/Application/HID/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/Application/Layer/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/Application/LayerStack/*.cpp"
	"${CMAKE_SOURCE_DIR}/src/Core/*.cpp"
)

add_executable (BlockForge ${SOURCE_FILES})

include_directories(BlockForge 
    PRIVATE 
    "${CMAKE_SOURCE_DIR}/include"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET BlockForge PROPERTY CXX_STANDARD 20)
endif()

# Dependencies
set(dep_directories "AMQP-CPP")
set(dep_packages "amqpcpp")

# Automated dependencies linking
#foreach(dep IN ZIP_LISTS dep_directories dep_packages)
#	set(${dep_1}_DIR "${CMAKE_SOURCE_DIR}/../dependencies/${dep_0}/build/cmake")
#	find_package(${dep_1} REQUIRED CONFIG)
#	find_library(lib NAMES ${dep_1} PATHS "${CMAKE_SOURCE_DIR}/../dependencies/${dep_0}/build/lib")
#	include_directories("${CMAKE_SOURCE_DIR}/../dependencies/${dep_0}/build/include")
#	target_link_libraries(${PROJECT_NAME} ${lib})
#endforeach()
