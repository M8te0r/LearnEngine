set(TARGET_NAME "KaleidoscopeSandbox")

file(GLOB_RECURSE sandbox_head_files "${CMAKE_CURRENT_SOURCE_DIR}/*.h")
file(GLOB_RECURSE sandbox_source_files "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

add_executable(${TARGET_NAME} ${sandbox_head_files} ${sandbox_source_files}  )
# add_dependencies(${TARGET_NAME}  Engine)

target_link_libraries(${TARGET_NAME}  Engine)

# 预编译文件
# target_precompile_headers(
#     ${TARGET_NAME}  
#     PRIVATE
#     ${engine_root_dir}/src/kldpch.h
# )


target_precompile_headers(
    ${TARGET_NAME} 
    REUSE_FROM 
    Engine
    )

target_include_directories(
    ${TARGET_NAME} 
    PRIVATE
    ${sandbox_root_dir}
    # ${app_root_dir}
    ${engine_root_dir}/src
    ${engine_root_dir}/vendor/imgui
    ${engine_root_dir}/vendor/glm
    ${engine_root_dir}/vendor/entt/include
    

    )