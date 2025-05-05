#pragma once

// Internal Headers
# include "debug.hpp"
# include "Grid.hpp"
# include "SandBlock.hpp"
# include "WaterBlock.hpp"
# include "StoneBlock.hpp"

// External Libraries
# include <GLAD/glad.h>
# include <GLFW/glfw3.h>

// Standard Libraries
# include <iostream>
# include <string>
# include <sstream>
# include <fstream>
# include <chrono>

// Standard STL Libraries
# include <vector>

// Constants
# define WINDOW_WIDTH	1000
# define WINDOW_HEIGHT	1000
# define WINDOW_TITLE	"OpenGL Sandbox"
# define GRID_SIZE		100

// Init functions
bool	initGLFW(GLFWwindow *&window);
bool	initGLAD();
bool	initShader(unsigned int &shader);
