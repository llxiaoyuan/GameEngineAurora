#include<Aurora.hpp>

#include"MyGame.hpp"

int main()
{
	Configuration config;
	config.screenWidth = 960;
	config.screenHeight = 540;
	config.title = "Aurora Test";
	Aurora::get().iniEngine(config);
	Aurora::get().iniGame(new MyGame());
	return 0;
}