#pragma once

# include "debug.hpp"

# include <GLAD/glad.h>
# include <GLFW/glfw3.h>

# include <iostream>
# include <string>
# include <sstream>
# include <fstream>

# include <vector>

# define WINDOW_WIDTH	800
# define WINDOW_HEIGHT	800
# define GRID_WIDTH		100
# define GRID_HEIGHT	100

bool	initGLFW(GLFWwindow *&window);
bool	initGLAD();

unsigned int	initShader();
