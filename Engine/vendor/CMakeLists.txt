

# spdlog
# set(SPDLOG_BUILD_SHARED OFF)
# set(SPDLOG_BUILD_EXAMPLE OFF)
# set(SPDLOG_BUILD_EXAMPLE_HO OFF)
# set(SPDLOG_BUILD_TESTS OFF)
# set(SPDLOG_BUILD_TESTS_HO OFF)
# set(SPDLOG_BUILD_BENCH OFF)
# set(SPDLOG_SANITIZE_ADDRESS OFF)
# set(SPDLOG_INSTALL OFF)
# set(SPDLOG_FMT_EXTERNAL OFF)
# set(SPDLOG_FMT_EXTERNAL_HO OFF)
# set(SPDLOG_NO_EXCEPTIONS OFF)
# set(spdlog_root ${CMAKE_CURRENT_SOURCE_DIR}/spdlog)
set(spdlog_include_dir   ${spdlog_root}/include)
add_subdirectory(spdlog)

# glfw
option(GLFW_BUILD_EXAMPLES "" OFF)
option(GLFW_BUILD_TESTS "" OFF)
option(GLFW_BUILD_DOCS "" OFF)
option(GLFW_INSTALL "" OFF)
add_subdirectory(glfw)

# glad
set(glad_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
set(glad_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/glad/src)
# list(APPEND include_dir "${glad_include_dir}")
file(GLOB_RECURSE glad_headers  "${CMAKE_CURRENT_SOURCE_DIR}/glad/*.h")
file(GLOB_RECURSE glad_sources  "${CMAKE_CURRENT_SOURCE_DIR}/glad/*.c")
add_library(glad STATIC ${glad_headers} ${glad_sources})
target_include_directories(glad PUBLIC ${glad_src_dir} ${glad_include_dir})






