cmake_minimum_required(VERSION 3.15)

project(BlockForgeTests)

# Add source files for tests
file(GLOB_RECURSE TEST_SOURCE_FILES
    "${CMAKE_SOURCE_DIR}/test/src/*.cpp"
)

# GoogleTest
add_subdirectory("${CMAKE_SOURCE_DIR}/lib/googletest")
include_directories("${CMAKE_SOURCE_DIR}/lib/googletest/include")

# Set up the test executable
add_executable(BlockForgeTests ${TEST_SOURCE_FILES})

# Link the test executable with your project's static libraries and GoogleTest
target_link_libraries(BlockForgeTests
    PRIVATE
    ${PROJECT_NAME}
    gtest_main
)

# Include directories for your project
target_include_directories(BlockForgeTests
    PRIVATE
    "${CMAKE_SOURCE_DIR}/include"
)

# Include directories for test-specific dependencies, if any
target_include_directories(BlockForgeTests
    PRIVATE
    "${CMAKE_SOURCE_DIR}/test/include"
)

# Optional: Set additional compile definitions for tests
# target_compile_definitions(BlockForgeTests
#     PRIVATE
#     MY_TEST_DEFINE
# )

# Optional: Set compiler flags for tests
# target_compile_options(BlockForgeTests
#     PRIVATE
#     -Wall
#     -Wextra
# )

# Optional: Copy test resource files to the build directory
# configure_file(${CMAKE_SOURCE_DIR}/test/resources/resource.txt ${CMAKE_CURRENT_BINARY_DIR}/resource.txt COPYONLY)

# Register the test with CTest
include(GoogleTest)
gtest_discover_tests(BlockForgeTests)
