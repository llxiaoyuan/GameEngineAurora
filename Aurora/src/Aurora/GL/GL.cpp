#include<Aurora/GL/GL.hpp>

FBO* GL::createFBO(const int& width, const int& height, const float& r, const float& g, const float& b, const float& a)
{
	return new FBO(width, height, r, g, b, a);
}

FBO* GL::createFBO(const int& width, const int& height, const int& internalFormat, const unsigned int& format, const unsigned int& type, const int& param)
{
	return new FBO(width,height, internalFormat,format,type,param);
}

void GL::enable(const unsigned int& cap)
{
	glEnable(cap);
}

void GL::disable(const unsigned int& cap)
{
	glDisable(cap);
}

void GL::clear(const unsigned int& mask)
{
	glClear(mask);
}

void GL::clearColor(const float& r, const float& g, const float& b, const float& a)
{
	glClearColor(r, g, b, a);
}

void GL::viewport(const int& x, const int& y, const int& width, const int& height)
{
	glViewport(x, y, width, height);
}

void GL::uniform1i(const int& location, const int& v0)
{
	glUniform1i(location, v0);
}

void GL::uniform1f(const int& location, const float& v0)
{
	glUniform1f(location, v0);
}

void GL::uniform2f(const int& location, const float& v0, const float& v1)
{
	glUniform2f(location, v0, v1);
}

void GL::uniform3f(const int& location, const float& v0, const float& v1, const float& v2)
{
	glUniform3f(location, v0, v1, v2);
}

void GL::uniform4f(const int& location, const float& v0, const float& v1, const float& v2, const float& v3)
{
	glUniform4f(location, v0, v1, v2, v3);
}
