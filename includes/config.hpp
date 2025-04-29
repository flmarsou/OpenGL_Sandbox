#pragma once

// External Libraries
# include <GLAD/glad.h>
# include <GLFW/glfw3.h>

// Standard Libraries
# include <iostream>
# include <string>
# include <sstream>
# include <fstream>

// Standard STL Libraries
# include <vector>

// Constants
# define WINDOW_WIDTH	1000
# define WINDOW_HEIGHT	1000
# define WINDOW_TITLE	"OpenGL Sandbox"
# define GRID_WIDTH		100
# define GRID_HEIGHT	100
# define ERROR		"\e[31m[x] - Error: \e[0m"
# define SUCCESS	"\e[32m[v] - Success: \e[0m"
# define WARNING	"\e[35m[!] - Warning: \e[0m"
# define INFO		"\e[36m[i] - Info: \e[0m"


bool	initGLFW(GLFWwindow *&window);
bool	initGLAD();

unsigned int	initShader();
