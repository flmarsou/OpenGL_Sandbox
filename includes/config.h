#pragma once

# include "debug.h"

# include <GLAD/glad.h>
# include <GLFW/glfw3.h>
# include <iostream>
# include <string>
# include <sstream>
# include <fstream>

unsigned int	makeModule(const std::string &filePath, unsigned int moduleType);
