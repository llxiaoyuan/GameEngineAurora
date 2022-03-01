#include"Shader.hpp"

std::vector<std::string> Shader::ParseShader(const std::string& filePath)
{
	std::ifstream stream(filePath);

	if (stream.fail())
	{
		std::cout << "FAILURE\n";
		return std::vector<std::string>{};
	}

	enum class ShaderEnum
	{
		NONE = -1, VERTEX, FRAGMENT, GEOMETRY
	}shaderenum = ShaderEnum::NONE;

	std::stringstream ss[3];

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
		else
		{
			ss[(int)shaderenum] << line << '\n';
		}
	}

	std::cout << "["<<typeid(*this).name()<<"] " << filePath << " compile ";

	return std::vector<std::string>{ ss[0].str(), ss[1].str(), ss[2].str() };
}

unsigned int Shader::CompileShader(const std::string& source, GLenum type)
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

unsigned int Shader::CreateShader(const std::vector<std::string> shaderSource)
{
	unsigned int program = glCreateProgram();

	unsigned int vs = 0, fs = 0, gs = 0;

	for (int i = 0; i < shaderSource.size(); i++)
	{
		if (shaderSource[i] == "")
		{
			continue;
		}
		switch (i)
		{
		case 0UL:
			vs = CompileShader(shaderSource[0], GL_VERTEX_SHADER);
			glAttachShader(program, vs);
			glDeleteShader(vs);
			break;
		case 1UL:
			fs = CompileShader(shaderSource[1], GL_FRAGMENT_SHADER);
			glAttachShader(program, fs);
			glDeleteShader(fs);
			break;
		case 2UL:
			gs = CompileShader(shaderSource[2], GL_GEOMETRY_SHADER);
			glAttachShader(program, gs);
			glDeleteShader(gs);
			break;
		default:
			break;
		}
	}

	glLinkProgram(program);
	glValidateProgram(program);

	std::cout << "success!\n";

	return program;
}

Shader::Shader()
{
	programID = 0;
}

Shader::~Shader()
{
	glUseProgram(0);
	glDeleteProgram(programID);
}

void Shader::create(const std::string& filePath)
{
	programID = CreateShader(ParseShader(filePath));
}

void Shader::bind() const
{
	glUseProgram(programID);
}

void Shader::unbind() const
{
	glUseProgram(0);
}

void Shader::setMatrix4fv(const char* name, const glm::mat4& mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(programID, name), 1, GL_FALSE, &mat[0][0]);
}

void Shader::setVec4f(const char* name, const float& x, const float& y, const float& z, const float& w) const
{
	glUniform4f(glGetUniformLocation(programID, name), x, y, z, w);
}

