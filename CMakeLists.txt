cmake_minimum_required(VERSION 3.10.0)

project(CppDataStructure
    VERSION 1.0
    DESCRIPTION "C++一些数据结构的实现"
    HOMEPAGE_URL "https://github.com/Sky101223/Cpp-DataStructure"
    LANGUAGES CXX
)

# 设置C++标准
set(CMAKE_CXX_STANDARD 20)

# 设置可执行文件输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# 设置静态库输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 设置动态库输出目录
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

# 设置头文件目录
include_directories(include)

# 执行文件
add_executable(${PROJECT_NAME} src/Main.cpp)
