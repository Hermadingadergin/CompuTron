cmake_minimum_required(VERSION 3.10)
# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
# used internally by CMake to identify your project
project(CompuTron)
# Include the directory headers are located
include_directories(${CMAKE_SOURCE_DIR}/include)
# Add the main executable
add_executable(CompuTron src/main.cpp src/computron.cpp)
add_executable(my_test test/test.cpp src/computron.cpp)
#Include directories for the test target
target_include_directories(my_test PRIVATE ${PROJECT_SOURCE_DIR}/include)
#Enable testing
enable_testing()
#Register the test executable with CTest
add_test(NAME my_test COMMAND my_test)