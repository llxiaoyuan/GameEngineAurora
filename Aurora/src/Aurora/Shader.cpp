#include<Aurora/Shader.hpp>

std::vector<std::string> Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	if (stream.fail())
	{
		std::cout << "[class Shader] " << filePath << " load failed\n";
		return std::vector<std::string>{};
	}

	enum class ShaderEnum
	{
		NONE = -1, VERTEX, FRAGMENT, GEOMETRY, COMPUTE
	}shaderenum = ShaderEnum::NONE;

	std::stringstream ss[4];

	std::string line;

	while (std::getline(stream, line))
	{
		if (line == "VERTEX")
		{
			shaderenum = ShaderEnum::VERTEX;
		}
		else if (line == "FRAGMENT")
		{
			shaderenum = ShaderEnum::FRAGMENT;
		}
		else if (line == "GEOMETRY")
		{
			shaderenum = ShaderEnum::GEOMETRY;
		}
		else if (line == "COMPUTE")
		{
			shaderenum = ShaderEnum::COMPUTE;
		}
		else
		{
			if ((int)shaderenum >= 0)
			{
				ss[(int)shaderenum] << line << '\n';
			}
		}
	}

	std::cout << "[class Shader] " << filePath << " compile ";

	return std::vector<std::string>{ ss[0].str(), ss[1].str(), ss[2].str(), ss[3].str() };
}

unsigned int Shader::CompileShader(const std::string& source, const GLenum& type)
{

	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;

	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = new char[length];
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << message << "\n";
		delete[] message;
		glDeleteShader(id);
		return 0;
	}

	return id;
}

unsigned int Shader::CreateShader(const std::vector<std::string>& shaderSource)
{
	unsigned int program = glCreateProgram();

	unsigned int vs = 0, fs = 0, gs = 0, cs = 0;

	bool succeed = true;

	for (int i = 0; i < shaderSource.size(); i++)
	{
		if (shaderSource[i] == "")
		{
			continue;
		}
		switch (i)
		{
		case 0UL:
			if (!(vs = CompileShader(shaderSource[0], GL_VERTEX_SHADER)))
			{
				succeed = false;
			}
			glAttachShader(program, vs);
			glDeleteShader(vs);
			break;
		case 1UL:
			if (!(fs = CompileShader(shaderSource[1], GL_FRAGMENT_SHADER)))
			{
				succeed = false;
			}
			glAttachShader(program, fs);
			glDeleteShader(fs);
			break;
		case 2UL:
			if (!(gs = CompileShader(shaderSource[2], GL_GEOMETRY_SHADER)))
			{
				succeed = false;
			}
			glAttachShader(program, gs);
			glDeleteShader(gs);
			break;
		case 3UL:
			if (!(cs = CompileShader(shaderSource[3], GL_COMPUTE_SHADER)))
			{
				succeed = false;
			}
			glAttachShader(program, cs);
			glDeleteShader(cs);
		default:
			break;
		}
	}

	glLinkProgram(program);
	glValidateProgram(program);

	if (succeed)
	{
		std::cout << "success!\n";
	}
	else
	{
		std::cout << "failed\n";
	}

	return program;
}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(programID);
}

Shader::Shader(const std::string& filePath) :
	programID(CreateShader(ParseShader(filePath)))
{
	int uniformCount;
	glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &uniformCount);

	int maxUniformLen;
	glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLen);

	char* uniformName = new char[maxUniformLen];

	for (int index = 0; index < uniformCount; index++)
	{
		int size;

		unsigned int type;

		glGetActiveUniform(programID, index, maxUniformLen, nullptr, &size, &type, uniformName);

		const int location = glGetUniformLocation(programID, uniformName);

		uniforms.insert(std::pair<std::string,const int>(uniformName, location));
	}

	delete[] uniformName;
}

Shader::Shader(const std::string& vertPath, const std::string& fragPath):
	programID(0)
{
	programID = glCreateProgram();

	unsigned int vs = 0;
	unsigned int fs = 0;

	bool succeed = true;

	std::string vertSource = Utils::File::readAllText(vertPath);
	std::string fragSource = Utils::File::readAllText(fragPath);

	vs = CompileShader(vertSource, GL_VERTEX_SHADER);

	if (vertSource=="")
	{
		std::cout << "[class Shader] vertex shader file is empty!\n";
	}

	if (fragSource == "")
	{
		std::cout << "[class Shader] fragment shader file is empty!\n";
	}

	std::cout << "[class Shader] " << vertPath << " VertexShader compile ";
	if (vs)
	{
		std::cout << "succeed!\n";
	}
	else
	{
		std::cout << "failed!\n";
	}

	glAttachShader(programID, vs);
	glDeleteShader(vs);

	fs = CompileShader(fragSource, GL_FRAGMENT_SHADER);

	std::cout << "[class Shader] " << fragPath << " FragmentShader compile ";
	if (fs)
	{
		std::cout << "succeed!\n";
	}
	else
	{
		std::cout << "failed!\n";
	}

	glAttachShader(programID, fs);
	glDeleteShader(fs);

	glLinkProgram(programID);
	glValidateProgram(programID);

	int uniformCount;
	glGetProgramiv(programID, GL_ACTIVE_UNIFORMS, &uniformCount);

	int maxUniformLen;
	glGetProgramiv(programID, GL_ACTIVE_UNIFORM_MAX_LENGTH, &maxUniformLen);

	char* uniformName = new char[maxUniformLen];

	for (int index = 0; index < uniformCount; index++)
	{
		int size;

		unsigned int type;

		glGetActiveUniform(programID, index, maxUniformLen, nullptr, &size, &type, uniformName);

		const int location = glGetUniformLocation(programID, uniformName);

		uniforms.insert(std::pair<std::string,const int>(uniformName, location));
	}

	delete[] uniformName;
}

Shader* Shader::create(const std::string& filePath)
{
	return new Shader(filePath);
}

Shader* Shader::create(const std::string& vertPath, const std::string& fragPath)
{
	return new Shader(vertPath, fragPath);
}

void Shader::bind() const
{
	glUseProgram(programID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

int Shader::getUniformLocation(const char* name) const
{
	return glGetUniformLocation(programID, name);
}

void Shader::setMatrix4fv(const char* name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec1i(const int& location, const int& value) const
{
	glUniform1i(location, value);
}

void Shader::setVec1f(const int& location, const float& value) const
{
	glUniform1f(location, value);
}

void Shader::setVec4f(const char* name, const float& x, const float& y, const float& z, const float& w) const
{
	glUniform4f(glGetUniformLocation(programID, name), x, y, z, w);
}

void Shader::setVec4f(const int& location, const float& x, const float& y, const float& z, const float& w) const
{
	glUniform4f(location, x, y, z, w);
}

int Shader::operator[](const std::string& str)
{
	return uniforms[str];
}

