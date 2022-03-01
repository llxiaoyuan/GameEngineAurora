#pragma once

#ifndef _SHADER_HPP_
#define _SHADER_HPP_

#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<iostream>
#include<glad/glad.h>
#include<glm/glm.hpp>

class Shader
{
public:

	Shader();

	~Shader();

	void create(const std::string& filePath);

	void bind() const;

	void unbind() const;

	void setMatrix4fv(const char* name, const glm::mat4& mat) const;

	void setVec4f(const char* name, const float& x, const float& y, const float& z, const float& w) const;

private:

	unsigned int programID;

	std::vector<std::string> ParseShader(const std::string& filePath);

	unsigned int CompileShader(const std::string& source, GLenum type);

	unsigned int CreateShader(const std::vector<std::string> shaderSource);

};

#endif // !_SHADER_HPP_
