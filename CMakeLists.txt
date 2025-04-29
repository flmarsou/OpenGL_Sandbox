cmake_minimum_required(VERSION 3.10.0)
project("OpenGL Sandbox")

# Executables
add_executable(opengl_sandbox
	libs/GLAD/glad.c
	src/main.cpp
	src/init.cpp
	src/shaders.cpp
	src/block/Block.cpp
	src/grid/Grid.cpp
)

# Includes
target_include_directories(opengl_sandbox PRIVATE
	${CMAKE_SOURCE_DIR}/libs
	${CMAKE_SOURCE_DIR}/includes
	${CMAKE_SOURCE_DIR}/src/block
	${CMAKE_SOURCE_DIR}/src/grid
)

# Compilation Flags
target_compile_options(opengl_sandbox PRIVATE
	-Wall -Wextra -O2
)

# ---------------------------------------------------------------------------- #
#   Windows-specific                                                           #
# ---------------------------------------------------------------------------- #
if (WIN32)
	# Libraries
	target_link_libraries(opengl_sandbox PRIVATE
		"${CMAKE_SOURCE_DIR}/libs/GLFW/libglfw3dll.a"
	)

	add_custom_command(TARGET opengl_sandbox POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		"${CMAKE_SOURCE_DIR}/libs/GLFW/glfw3.dll"
		$<TARGET_FILE_DIR:opengl_sandbox>
	)

# ---------------------------------------------------------------------------- #
#   Linux-specific                                                             #
# ---------------------------------------------------------------------------- #
elseif (UNIX)
	# Libraries
	target_link_libraries(opengl_sandbox PRIVATE
		glfw
	)

endif()
