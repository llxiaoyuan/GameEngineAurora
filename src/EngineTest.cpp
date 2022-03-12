#include<Aurora/Aurora.hpp>

#include"MyGame.hpp"

int main()
{
	Configuration config(1920, 1080, u8"Aurora Test", Configuration::DisplayMode::Normal, true, 2, 5600, 5);
	Aurora::get().iniEngine(config);
	Aurora::get().iniGame(new MyGame());
	return 0;
}