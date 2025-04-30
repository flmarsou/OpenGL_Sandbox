#include "config.hpp"

static unsigned int	makeModule(const std::string &filePath, unsigned int moduleType)
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

static unsigned int	makeShader(const std::vector<unsigned int> &modules)
{
	unsigned int				shader;

	// Creates and links the shaders
	shader = glCreateProgram();
	for (unsigned int i = 0; i < modules.size(); i++)
		glAttachShader(shader, modules[i]);
	glLinkProgram(shader);

	// Checks for linking errors
	int	status;

	glGetProgramiv(shader, GL_LINK_STATUS, &status);
	if (!status)
	{
		char	log[512];
		glGetShaderInfoLog(shader, sizeof(log), NULL, log);
		std::cerr << ERROR "Shaders linking failed!" << std::endl;
		return (0);
	}
	std::cout << SUCCESS "Shaders linked!" << std::endl;

	// Deletes the compiled shaders
	for (unsigned i = 0; i < modules.size(); i++)
		glDeleteShader(modules[i]);

	return (shader);
}

bool	initShader(unsigned int &shader)
{
	std::vector<unsigned int>	modules;

	modules.push_back(makeModule("../shaders/vertex.glsl", GL_VERTEX_SHADER));
	modules.push_back(makeModule("../shaders/fragment.glsl", GL_FRAGMENT_SHADER));

	shader = makeShader(modules);

	if (shader == 0)
		return (false);
	return (true);
}
