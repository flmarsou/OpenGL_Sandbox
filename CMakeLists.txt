cmake_minimum_required(VERSION 3.10.0)
project("OpenGL Sandbox")

# Executables
add_executable(opengl_sandbox
	libs/GLAD/glad.c
	src/main.cpp
	src/util/init.cpp
	src/util/shaders.cpp
	src/util/debug.cpp
	src/input.cpp
	src/loop.cpp
	src/grid/Grid.cpp
	src/block/ABlock.cpp
	src/block/powder/SandBlock.cpp
	src/block/liquid/WaterBlock.cpp
	src/block/solid/StoneBlock.cpp
	src/block/reactive/BombBlock.cpp
	src/block/reactive/FireBlock.cpp
	src/block/liquid/AcidBlock.cpp
	src/block/solid/WoodBlock.cpp
	src/block/powder/AshBlock.cpp
	src/block/liquid/ToxicSludgeBlock.cpp
	src/block/gas/FlammableGasBlock.cpp
)

# Includes
target_include_directories(opengl_sandbox PRIVATE
	${CMAKE_SOURCE_DIR}/libs
	${CMAKE_SOURCE_DIR}/includes
	${CMAKE_SOURCE_DIR}/src/block
	${CMAKE_SOURCE_DIR}/src/block/gas
	${CMAKE_SOURCE_DIR}/src/block/liquid
	${CMAKE_SOURCE_DIR}/src/block/powder
	${CMAKE_SOURCE_DIR}/src/block/reactive
	${CMAKE_SOURCE_DIR}/src/block/solid
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
