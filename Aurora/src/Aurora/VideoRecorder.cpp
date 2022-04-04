#include<Aurora/VideoRecorder.hpp>

VideoRecorder::VideoRecorder(const int& _width, const int& _height, const size_t& _totalFrame, const int& _frameRate) :
	width(_width), height(_height), byteNum(_width* _height * 4), curIndex(0), pbos(new unsigned int[pboNum]), frameRecorded(0), totalFrame(_totalFrame),frameTime(0)
{
	glGenBuffers(pboNum, pbos);
	for (size_t i = 0; i < pboNum; i++)
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbos[i]);
		glBufferData(GL_PIXEL_PACK_BUFFER, byteNum, nullptr, GL_STREAM_READ);
	}
	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	const std::string cmd = "ffmpeg -r " + std::to_string(_frameRate) + " -f rawvideo -pix_fmt rgba -s " + std::to_string(width) + "x" + std::to_string(height) + " -i - " + "-threads 0 -tune zerolatency -preset ultrafast -y -pix_fmt yuv420p -vf vflip -crf 21 -an output.mp4";

	std::cout << "[class VideoRecorder] render at " << width << "x" << height << "\n";
	std::cout << "[class VideoRecorder] FPS:" << _frameRate << "\n";
	std::cout << "[class VideoRecorder] total frame " << totalFrame << "\n";

	stream = _popen(cmd.c_str(), "wb");

}

VideoRecorder::~VideoRecorder()
{
	glDeleteBuffers(pboNum, pbos);
}

bool VideoRecorder::record()
{

	if (frameRecorded < pboNum)
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbos[curIndex]);
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	}
	else
	{
		glBindBuffer(GL_PIXEL_PACK_BUFFER, pbos[curIndex]);
		const unsigned char* const ptr = (unsigned char*)glMapBuffer(GL_PIXEL_PACK_BUFFER, GL_READ_ONLY);
		if (ptr)
		{
			timeStart = timer.now();
			fwrite(ptr, byteNum, 1, stream);
			timeEnd = timer.now();
			frameTime += std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count() / 1000.f;
			glUnmapBuffer(GL_PIXEL_PACK_BUFFER);
		}
		else
		{
			std::cout << "[class VideoRecorder] ptr is nullptr\n";
		}
		glReadPixels(0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, 0);
	}

	++frameRecorded;
	++curIndex;
	curIndex = curIndex % pboNum;

	glBindBuffer(GL_PIXEL_PACK_BUFFER, 0);

	if (frameRecorded == totalFrame + pboNum)
	{
		if (stream)
		{
			_pclose(stream);
		}
		std::cout << "[class VideoRecorder] frame record avg time " << frameTime / totalFrame << "\n";
		return false;
	}
	else
	{
		return true;
	}

}
