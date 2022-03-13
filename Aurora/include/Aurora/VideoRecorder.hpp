#pragma once

#ifndef _VIDEO_RECORDER_HPP_
#define _VIDEO_RECORDER_HPP_

#include<glad/glad.h>
#include<string.h>
#include<string>
#include<iostream>

class VideoRecorder
{
public:

	VideoRecorder(const int& width, const int& height,const size_t& frameTotal,const size_t& interval);

	~VideoRecorder();

	bool record();

private:

	static constexpr size_t pboNum = 8;

	unsigned int* pbos;

	size_t curIndex;

	size_t frameRecorded;

	const size_t frameTotal;

	const int width;

	const int height;

	const int byteNum;

	unsigned char* pixels;

	FILE* stream;

	size_t intervalCount;

	const size_t interval;

};

#endif // !_VIDEO_RECORDER_HPP_