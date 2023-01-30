# CMakeList.txt: Render_tick 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("Render_tick")

set(CMAKE_CXX_STANDARD 17)

#将子文件夹纳入编译系统
add_subdirectory(application)

#将静态资源放入到可执行文件目录下
file(GLOB ASSECTS "./asset")
file(COPY ${ASSECTS} DESTINATION ${CMAKE_BINARY_DIR})
message(${CMAKE_BINARY_DIR})


# 将源代码添加到此项目的可执行文件。
add_executable (Render  "main.cpp" )

target_link_libraries(Render application)
