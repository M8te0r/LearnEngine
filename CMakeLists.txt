cmake_minimum_required(VERSION 3.22)
project(Kaleidoscope VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "MSVC")
message("CMAKE_CXX_COMPILER_ID： ${CMAKE_CXX_COMPILER_ID}")
else()
set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -Wall -Wformat")
endif()
# set(CMAKE_CXX_FLAGS "${CAMKE_CXX_FLAGS} -Wall -O3")

# 可执行文件输出路径
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)


set(app_root_dir ${CMAKE_CURRENT_SOURCE_DIR})
# set(3rd_root_dir ${app_root_dir}/3rdparty)
set(engine_root_dir ${app_root_dir}/Engine)
set(sandbox_root_dir ${app_root_dir}/Sandbox)
set(editor_root_dir ${app_root_dir}/Editor)

add_subdirectory(Engine)
add_subdirectory(Sandbox)
add_subdirectory(Editor)


