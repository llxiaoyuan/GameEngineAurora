#pragma once

#include<Aurora/GL/GL.hpp>

class DoubleFBO
{
public:

	DoubleFBO(const int& w,const int& h,const int& internalFormat,const unsigned int& format,const unsigned int& type,const int& param):
		fbo1(GL::createFBO(w,h,internalFormat,format,type,param)),
		fbo2(GL::createFBO(w, h, internalFormat, format, type, param)),
		width(w),
		height(h)
	{
		texelSizeX = fbo1->texelSizeX;
		texelSizeY = fbo1->texelSizeY;
	}

	~DoubleFBO()
	{
		if (fbo1)
		{
			delete fbo1;
		}
		if (fbo2)
		{
			delete fbo2;
		}
	}

	FBO* fbo1;
	FBO* fbo2;

	int width;
	int height;
	float texelSizeX;
	float texelSizeY;

	FBO* read()
	{
		return fbo1;
	}

	void read(FBO* const fbo)
	{
		delete fbo1;
		fbo1 = fbo;
	}

	FBO* write()
	{
		return fbo2;
	}

	void write(FBO* const fbo)
	{
		delete fbo2;
		fbo2 = fbo;
	}

	void swap()
	{
		FBO* const temp = fbo1;
		fbo1 = fbo2;
		fbo2 = temp;
	}

};