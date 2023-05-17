set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME} SandboxApp.cpp)
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
    # ${app_root_dir}
    ${engine_root_dir}/src
    ${engine_root_dir}/vendor/imgui
    ${engine_root_dir}/vendor/glm

    )