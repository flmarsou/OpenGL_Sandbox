cmake_minimum_required(VERSION 3.10.0)
project("OpenGL Sandbox")

# Executables
add_executable(opengl_sandbox
	libs/GLAD/glad.c
	libs/IMGUI/imgui.cpp
	libs/IMGUI/imgui_draw.cpp
	libs/IMGUI/imgui_tables.cpp
	libs/IMGUI/imgui_widgets.cpp
	libs/IMGUI/imgui_demo.cpp
	libs/IMGUI/imgui_impl_glfw.cpp
	libs/IMGUI/imgui_impl_opengl3.cpp
	src/main.cpp
	src/util/init.cpp
	src/util/shaders.cpp
	src/util/input.cpp
	src/loop.cpp
	src/grid/Grid.cpp
	src/block/ABlock.cpp
	src/block/electricity/AElectricity.cpp
	src/block/electricity/BatteryBlock.cpp
	src/block/electricity/RedLedBlock.cpp
	src/block/electricity/GreenLedBlock.cpp
	src/block/electricity/BlueLedBlock.cpp
	src/block/electricity/C4Block.cpp
	src/block/gas/AGas.cpp
	src/block/gas/FlammableGasBlock.cpp
	src/block/gas/SteamBlock.cpp
	src/block/liquid/ALiquid.cpp
	src/block/liquid/AcidBlock.cpp
	src/block/liquid/OilBlock.cpp
	src/block/liquid/ToxicSludgeBlock.cpp
	src/block/liquid/WaterBlock.cpp
	src/block/powder/APowder.cpp
	src/block/powder/AshBlock.cpp
	src/block/powder/MudBlock.cpp
	src/block/powder/SandBlock.cpp
	src/block/reactive/BombBlock.cpp
	src/block/reactive/FireBlock.cpp
	src/block/solid/MetalBlock.cpp
	src/block/solid/StoneBlock.cpp
	src/block/solid/WoodBlock.cpp
)

# Includes
target_include_directories(opengl_sandbox PRIVATE
	${CMAKE_SOURCE_DIR}/libs
	${CMAKE_SOURCE_DIR}/includes
	${CMAKE_SOURCE_DIR}/src/block
	${CMAKE_SOURCE_DIR}/src/block/electricity
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
