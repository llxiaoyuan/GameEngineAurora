#include<Aurora.hpp>

#include"MyGame.hpp"

int main()
{
	Configuration config(960,540,"Aurora Test");
	Aurora::get().iniEngine(config);
	Aurora::get().iniGame(new MyGame());
	return 0;
}