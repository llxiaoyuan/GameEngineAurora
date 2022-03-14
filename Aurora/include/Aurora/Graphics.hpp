#pragma once

#ifndef _GRAPHICS_HPP_
#define _GRAPHICS_HPP_

class Graphics
{
public:

	struct RecordConfig
	{
		size_t totalFrame;
		int frameRate;
	};

	//获取变化的时间
	static const float& getDeltaTime();

	//获取窗口宽
	static const int& getWidth();

	//获取窗口高
	static const int& getHeight();

	//获取帧数
	static const float& getFPS();

	static void setRecordConfig(const RecordConfig& config);

private:

	//帧数
	static float FPS;

	static float frameDuration;

	static int frameCount;

	//窗口宽
	static int screenWidth;

	//窗口高
	static int screenHeight;

	//变化的时间
	static float deltaTime;

	static RecordConfig config;

	friend class Aurora;

};

#endif // !_GRAPHICS_HPP_