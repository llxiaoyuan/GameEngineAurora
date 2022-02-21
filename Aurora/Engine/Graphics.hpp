#pragma once

#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

#include"Aurora.hpp"

class Graphics
{
public:

	static const float& getDeltaTime();

	static void setDeltaTime(const float& dt);

	static const int& getWidth();

	static const int& getHeight();

	static const float& getFPS();

private:

	static float FPS;

	static float frameDuration;

	static int frameCount;

	static int screenWidth;

	static int screenHeight;

	static float deltaTime;

	friend class Aurora;

};

#endif // !_GRAPHICS_HPP_