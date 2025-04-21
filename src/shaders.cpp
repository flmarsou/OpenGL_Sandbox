#include "config.h"

unsigned int	makeModule(const std::string &filePath, unsigned int moduleType)
{
	// Read the file
	std::ifstream		file;
	std::stringstream	buffer;

	file.open(filePath);
	if (!file.is_open())
	{
		std::cerr << ERROR "Failed to open shader file: " << filePath << std::endl;
		return (0);
	}

	buffer << file.rdbuf();
	const std::string	shaderSourceTemp = buffer.str();
	const char			*shaderSource = shaderSourceTemp.c_str();

	file.close();

	// Creates and compiles the shader
	unsigned int	shader;
	shader = glCreateShader(moduleType);
	glShaderSource(shader, 1, &shaderSource, NULL);
	glCompileShader(shader);

	// Checks for compilation errors
	int	status;

	glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
	if (!status)
	{
		char	log[512];
		glGetShaderInfoLog(shader, sizeof(log), NULL, log);
		std::cerr << ERROR "Shader compilation failed in \"" << filePath << "\": " << log << std::endl;
		return (0);
	}
	std::cout << SUCCESS "Compiled shader \"" << filePath << "\"" << std::endl;

	return (shader);
}
