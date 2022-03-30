#pragma once

#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

class Graphics
{
public:

	Graphics() = delete;

	Graphics(const Graphics&) = delete;

	struct RecordConfig
	{
		size_t totalFrame;
		int frameRate;
	};

	static const float& getDeltaTime();

	static const int& getWidth();

	static const int& getHeight();

	static const float& getFPS();

	static void setRecordConfig(const RecordConfig& config);

private:

	static float framePerSec;

	static float frameDuration;

	static int frameCount;

	static int screenWidth;

	static int refreshRate;

	static float deltaTimeLimit;

	static int screenHeight;

	static float deltaTime;

	static RecordConfig config;

	friend class Aurora;

};

#endif // !_GRAPHICS_HPP_