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

};

#endif // !_GL_HPP_