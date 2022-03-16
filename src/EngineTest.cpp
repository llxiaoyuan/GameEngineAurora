#include<Aurora/Aurora.hpp>

#include"MyGame.hpp"

int main()
{
	Configuration config(350, 350, u8"Aurora Test", Configuration::DisplayMode::Normal, true, 2);
	Aurora::get().iniEngine(config);
	Aurora::get().iniGame(new MyGame());
	return 0;
}