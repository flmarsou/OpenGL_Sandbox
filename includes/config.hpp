#pragma once

// Internal Headers
# include "debug.hpp"
# include "input.hpp"

# include "Grid.hpp"

# include "SandBlock.hpp"
# include "WaterBlock.hpp"
# include "StoneBlock.hpp"
# include "BombBlock.hpp"
# include "FireBlock.hpp"
# include "AcidBlock.hpp"
# include "WoodBlock.hpp"
# include "MudBlock.hpp"

// External Libraries
# include <GLAD/glad.h>					// OpenGL Functions
# include <GLFW/glfw3.h>				// Window
# include <IMGUI/imgui.h>				// GUI
# include <IMGUI/imgui_impl_glfw.h>
# include <IMGUI/imgui_impl_opengl3.h>

// Standard Libraries
# include <string>
# include <sstream>
# include <fstream>
# include <chrono>

// Standard STL Libraries
# include <vector>

// Constants
# define WINDOW_WIDTH	900
# define WINDOW_HEIGHT	900
# define WINDOW_TITLE	"OpenGL Sandbox"
# define GRID_SIZE		100

// Init functions
bool	initGLFW(GLFWwindow *&window);
bool	initGLAD();
void	initImGui(GLFWwindow *&window);
bool	initShader(unsigned int &shader);
void	initCallbacks(GLFWwindow *window);

// Debug
void	printFPS();

// Main
void	gameLoop(GLFWwindow *window, const unsigned int &shader, Grid *grid);
