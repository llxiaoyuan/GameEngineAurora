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

	//��ȡ�仯��ʱ��
	static const float& getDeltaTime();

	//��ȡ���ڿ�
	static const int& getWidth();

	//��ȡ���ڸ�
	static const int& getHeight();

	//��ȡ֡��
	static const float& getFPS();

	static void setRecordConfig(const RecordConfig& config);

private:

	//֡��
	static float FPS;

	static float frameDuration;

	static int frameCount;

	//���ڿ�
	static int screenWidth;

	//���ڸ�
	static int screenHeight;

	//�仯��ʱ��
	static float deltaTime;

	static RecordConfig config;

	friend class Aurora;

};

#endif // !_GRAPHICS_HPP_