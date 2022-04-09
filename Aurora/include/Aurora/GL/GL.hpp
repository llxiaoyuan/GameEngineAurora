#pragma once

#ifndef _GL_HPP_
#define _GL_HPP_

#include"FBO.hpp"

class GL
{
public:

	GL() = delete;

	GL(const GL&) = delete;

	static FBO* createFBO(const int& width, const int& height, const float& r = 0, const float& g = 0, const float& b = 0, const float& a = 0);

	static FBO* createFBO(const int& width, const int& height, const int& internalFormat, const unsigned int& format, const unsigned int& type, const int& param);

	static void enable(const unsigned int& cap);

	static void disable(const unsigned int& cap);

	static void clear(const unsigned int& mask);

	static void clearColor(const float& r, const float& g, const float& b, const float& a = 1.f);

	static void viewport(const int& x, const int& y, const int& width, const int& height);

	static void uniform1i(const int& location, const int& v0);

	static void uniform1f(const int& location, const float& v0);

	static void uniform2f(const int& location, const float& v0,const float& v1);

	static void uniform3f(const int& location, const float& v0, const float& v1, const float& v2);

	static void uniform4f(const int& location, const float& v0, const float& v1, const float& v2, const float& v3);

};

#endif // !_GL_HPP_