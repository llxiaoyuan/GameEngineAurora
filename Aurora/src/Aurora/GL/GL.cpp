#include<Aurora/GL/GL.hpp>

FBO* GL::createFBO(const int& width, const int& height, const float& r, const float& g, const float& b, const float& a)
{
	return new FBO(width, height, r, g, b, a);
}

FBO* GL::createFBO(const int& width, const int& height, const int& internalFormat, const unsigned int& format, const unsigned int& type, const int& param)
{
	return new FBO(width,height, internalFormat,format,type,param);
}
