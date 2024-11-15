

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

# OpenGL
find_package(OpenGL REQUIRED)

# glm
add_subdirectory(glm)

# glad
set(glad_include_dir ${CMAKE_CURRENT_SOURCE_DIR}/glad/include)
set(glad_src_dir ${CMAKE_CURRENT_SOURCE_DIR}/glad/src)
file(GLOB_RECURSE glad_headers  "${CMAKE_CURRENT_SOURCE_DIR}/glad/*.h")
file(GLOB_RECURSE glad_sources  "${CMAKE_CURRENT_SOURCE_DIR}/glad/*.c")
add_library(glad STATIC ${glad_headers} ${glad_sources})
target_include_directories(glad PUBLIC ${glad_src_dir} ${glad_include_dir})
target_link_libraries(glad PRIVATE ${OPENGL_LIBRARIES})



# imgui
set(imgui_root_dir ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
file(GLOB imgui_sources   
    "${imgui_root_dir}/*.cpp"
    )
file(GLOB imgui_impl   
    "${imgui_root_dir}/backends/imgui_impl_glfw.cpp" 
    "${imgui_root_dir}/backends/imgui_impl_glfw.h"
    "${imgui_root_dir}/backends/imgui_impl_opengl3.cpp" 
    "${imgui_root_dir}/backends/imgui_impl_opengl3.h"
    )
add_library(imgui STATIC ${imgui_sources} ${imgui_impl})
target_include_directories(imgui PUBLIC ${imgui_root_dir} ${OPENGL_INCLUDE_DIR})
target_link_libraries(imgui PUBLIC glfw ${OPENGL_LIBRARIES})

# stb_image
set(stb_image_root_dir ${CMAKE_CURRENT_SOURCE_DIR}/stb)
file(GLOB_RECURSE stb_image_headers  "${CMAKE_CURRENT_SOURCE_DIR}/stb_image/*.h")
file(GLOB_RECURSE stb_image_sources  "${CMAKE_CURRENT_SOURCE_DIR}/stb_image/*.cpp")
add_library(stb_image STATIC ${stb_image_headers} ${stb_image_sources})
target_include_directories(stb_image PUBLIC ${stb_image_root_dir} )
# target_precompile_headers(
#     stb_image
#     PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/src/kldpch.h
# )

# target_include_directories(imgui PUBLIC ${OPENGL_INCLUDE_DIR})


# yaml
add_subdirectory(yaml-cpp)


# nativeFileDialog
set(native_file_dialog_root_dir ${CMAKE_CURRENT_SOURCE_DIR}/nativeFileDialog)
set(SOURCES ${native_file_dialog_root_dir}/src/nfd_common.c)
include(CheckIncludeFile)
macro(REQUIRE_INCLUDE_FILE path name)
    CHECK_INCLUDE_FILE(${path} ${name})
    if (NOT ${name})
        message(FATAL_ERROR "${path} not found")
    endif ()
endmacro()

# add specific implementations
if (WIN32)
    REQUIRE_INCLUDE_FILE(windows.h HAS_WINDOWS)
    list(APPEND SOURCES ${native_file_dialog_root_dir}/src/nfd_win.cpp)
elseif (APPLE)
    # 这个也不一定需要
    # REQUIRE_INCLUDE_FILE(AppKit/AppKit.h HAS_APPKIT)
    list(APPEND SOURCES ${native_file_dialog_root_dir}/src/nfd_cocoa.m)
elseif (UNIX)
    REQUIRE_INCLUDE_FILE(gtk/gtk.h HAS_GTK)
    list(APPEND SOURCES ${native_file_dialog_root_dir}/src/nfd_gtk.c)
elseif (UNIX)
    message(FATAL_ERROR "Cannot detect your system, please report to https://github.com/aarcangeli/nativefiledialog-cmake/issues")
endif ()

add_library(native_file_dialog STATIC ${SOURCES} )
target_include_directories(native_file_dialog PUBLIC ${native_file_dialog_root_dir}/src/include )


# ImGuizmo
set(imguizmo_root_dir ${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo)
file(GLOB_RECURSE imguizmo_headers  "${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo/ImGuizmo.h")
file(GLOB_RECURSE imguizmo_sources  "${CMAKE_CURRENT_SOURCE_DIR}/ImGuizmo/ImGuizmo.cpp")
add_library(ImGuizmo STATIC ${imguizmo_headers} ${imguizmo_sources})
target_include_directories(ImGuizmo PUBLIC ${imguizmo_root_dir} )
target_link_libraries(ImGuizmo PUBLIC imgui)

