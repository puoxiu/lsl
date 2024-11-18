cmake_minimum_required(VERSION 3.10)
project(SerialLib VERSION 1.0.0)

# 设置默认构建类型为 Debug
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 添加源文件目录
include_directories(src)

# 添加源文件
file(GLOB SOURCES "src/*.cpp")

# 添加库文件
add_library(serial_lib STATIC ${SOURCES})

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 打印构建类型
message(STATUS "Building with CMAKE_BUILD_TYPE: ${CMAKE_BUILD_TYPE}")

# 添加测试文件
file(GLOB TEST_SOURCES "test/*.cpp")

foreach(TEST_SOURCE IN LISTS TEST_SOURCES)
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME} PRIVATE serial_lib)
endforeach()