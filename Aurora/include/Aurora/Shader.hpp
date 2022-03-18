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

//着色器
class Shader
{
public:

	Shader();

	~Shader();

	//从文件创建着色器
	void create(const std::string& filePath);

	void bind() const;

	void unbind() const;

	int getUniformLocation(const char* name);

	void setMatrix4fv(const char* name, const glm::mat4& mat) const;
	
	void setVec1i(const int& location, const int& value) const;

	void setVec1f(const int& location, const float& value) const;

	void setVec4f(const char* name, const float& x, const float& y, const float& z, const float& w) const;

	void setVec4f(const int& location, const float& x, const float& y, const float& z, const float& w) const;

private:

	unsigned int programID;

	std::vector<std::string> ParseShader(const std::string& filePath);

	//编译着色器
	unsigned int CompileShader(const std::string& source, const GLenum& type);

	//创建着色器
	unsigned int CreateShader(const std::vector<std::string>& shaderSource);

};

#endif // !_SHADER_HPP_
