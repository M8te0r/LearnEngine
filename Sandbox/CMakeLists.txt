set(TARGET_NAME ${PROJECT_NAME})

add_executable(${TARGET_NAME} SandboxApp.cpp)

add_dependencies(${TARGET_NAME}  Engine)
target_link_libraries(${TARGET_NAME}  Engine)
target_include_directories(
    ${TARGET_NAME} 
    PRIVATE
    ${app_root_dir}
    )