cmake_minimum_required(VERSION 3.10.0)
project("OpenGL Sandbox")

find_package(OpenGL REQUIRED)

add_executable(opengl_sandbox
    libs/GLAD/glad.c
    src/main.cpp
)

target_include_directories(opengl_sandbox PRIVATE
    libs
    includes)

# if (WIN32)
    target_link_libraries(opengl_sandbox PRIVATE "${CMAKE_SOURCE_DIR}/libs/GLFW/libglfw3dll.a")

    add_custom_command(TARGET opengl_sandbox POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/libs/GLFW/glfw3.dll"
        $<TARGET_FILE_DIR:opengl_sandbox>
    )
# elseif (UNIX)
