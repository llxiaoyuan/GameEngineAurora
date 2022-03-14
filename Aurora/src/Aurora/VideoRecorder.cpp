#include<Aurora/VideoRecorder.hpp>

VideoRecorder::VideoRecorder(const int& _width, const int& _height, const size_t& _totalFrame,const int& frameRate) :
	width(_width), height(_height), byteNum(_width* _height * 4), curIndex(0), pbos(new unsigned int[pboNum]), pixels(nullptr), frameRecorded(0), totalFrame(_totalFrame)
{
	glGenBuffers(pboNum, pbos);
	for (size_t i = 0; i < pboNum; i++)
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbos[i]);
		glBufferData(GL_PIXEL_PACK_BUFFER, byteNum, nullptr, GL_STREAM_READ);
	}
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);
	pixels = new unsigned char[byteNum];

	const std::string cmd = "ffmpeg -r " +std::to_string(frameRate) + " -f rawvideo -pix_fmt rgba -s " + std::to_string(width) + "x" + std::to_string(height) + " -i - " + "-threads 0 -tune zerolatency -preset ultrafast -y -pix_fmt yuv420p -vf vflip -crf 21 -an output.mp4";

	std::cout << "Render at " << width << "x" << height << "\n";
	std::cout << "FPS:" << frameRate << "\n";
	std::cout << "Total Frame " << totalFrame << "\n";

	stream = _popen(cmd.c_str(), "wb");

}

VideoRecorder::~VideoRecorder()
{
	glDeleteBuffers(pboNum, pbos);
	if (pixels)
	{
		delete[] pixels;
	}
}

bool VideoRecorder::record()
{
	unsigned char* ptr = nullptr;

	if (frameRecorded < pboNum)
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbos[curIndex]);
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	}
	else
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbos[curIndex]);
		ptr = (unsigned char*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
		if (ptr)
		{
			memcpy(pixels, ptr, byteNum);
			fwrite(pixels, byteNum, 1, stream);
			glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		}
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	}

	++frameRecorded;
	++curIndex;
	curIndex = curIndex % pboNum;

	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	if (frameRecorded == totalFrame)
	{
		if (stream)
			_pclose(stream);
		return false;
	}
	else
	{
		return true;
	}

}
