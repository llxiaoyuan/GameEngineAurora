#include<Aurora/Aurora.hpp>

#include"MyGame.hpp"

int main(int argc, const char* argv[])
{
	int resolutionX = 1920;
	int resolutionY = 1080;
	std::string title = u8"Aurora Test";
	Configuration::DisplayMode displayMode = Configuration::DisplayMode::Normal;
	bool useAudio = true;
	int multisampleLevel = 4;

	Configuration config(resolutionX, resolutionY, title, displayMode, useAudio, multisampleLevel);
	if (Aurora::get().iniEngine(config))
	{
		Aurora::get().iniGame(new MyGame());
	}

	return 0;
}