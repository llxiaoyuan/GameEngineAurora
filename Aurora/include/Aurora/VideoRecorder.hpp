#pragma once

#ifndef _VIDEO_RECORDER_HPP_
#define _VIDEO_RECORDER_HPP_

#include<string>
#include<iostream>
#include<chrono>

#include<glad/glad.h>

class VideoRecorder
{
public:

	VideoRecorder() = delete;

	VideoRecorder(const VideoRecorder&) = delete;

	VideoRecorder(const int& width, const int& height,const size_t& totalFrame,const int& frameRate);

	void operator=(const VideoRecorder&) = delete;

	~VideoRecorder();

	bool record();

private:

	static constexpr size_t pboNum = 8;

	unsigned int* pbos;

	size_t curIndex;

	size_t frameRecorded;

	const size_t totalFrame;

	const int width;

	const int height;

	const int byteNum;

	FILE* stream;

	float frameTime;

	std::chrono::steady_clock timer;

	std::chrono::steady_clock::time_point timeStart;

	std::chrono::steady_clock::time_point timeEnd;

};

#endif // !_VIDEO_RECORDER_HPP_
