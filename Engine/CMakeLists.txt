set(LIB_NAME Engine)

file(GLOB_RECURSE engine_head_files "src/*.h")
file(GLOB_RECURSE engine_source_files "src/*.cpp")

# OpenGL
find_package(OpenGL REQUIRED)


add_subdirectory(vendor)
add_library(${LIB_NAME} ${engine_head_files} ${engine_source_files})


message(test ${spdlog_include_dir})
target_include_directories(
    ${LIB_NAME} 
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
    # ${glad_include_dir}
    # ${spdlog_include_dir}
    # ${imgui_root_dir}
    # ${OPENGL_INCLUDE_DIR}
    )

# 预编译文件
target_precompile_headers(
    ${LIB_NAME}  
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/kldpch.h
)

# 宏
# add_compile_definitions(GLFW_INCLUDE_NONE)
target_compile_definitions(
    ${LIB_NAME}  
    PRIVATE
    "GLFW_INCLUDE_NONE"
    )


target_link_libraries(
    ${LIB_NAME} 
    PUBLIC
    spdlog
    glfw
    OpenGL::GL
    glad
    imgui
)

