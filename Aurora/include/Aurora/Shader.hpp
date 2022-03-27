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

#include"Utils.hpp"

class Shader
{
public:

	~Shader();

	static Shader* create(const std::string& filePath);

	static Shader* create(const std::string& vertPath, const std::string& fragPath);

	void bind() const;

	void unbind() const;

	int getUniformLocation(const char* name);

	void setMatrix4fv(const char* name, const glm::mat4& mat) const;
	
	void setVec1i(const int& location, const int& value) const;

	void setVec1f(const int& location, const float& value) const;

	void setVec4f(const char* name, const float& x, const float& y, const float& z, const float& w) const;

	void setVec4f(const int& location, const float& x, const float& y, const float& z, const float& w) const;

private:

	Shader() = delete;

	Shader(const Shader&) = delete;

	void operator=(const Shader&) = delete;

	Shader(const std::string& filePath);

	Shader(const std::string& vertPath, const std::string& fragPath);

	unsigned int programID;

	std::vector<std::string> ParseShader(const std::string& filePath);

	unsigned int CompileShader(const std::string& source, const GLenum& type);

	unsigned int CreateShader(const std::vector<std::string>& shaderSource);

};

#endif // !_SHADER_HPP_
