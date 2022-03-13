#include<Aurora/Aurora.hpp>

#include"MyGame.hpp"

int main()
{
	Configuration config(1000, 1000, u8"Aurora Test", Configuration::DisplayMode::Record, true, 2, 600, 5);
	Aurora::get().iniEngine(config);
	Aurora::get().iniGame(new MyGame());
	return 0;
}