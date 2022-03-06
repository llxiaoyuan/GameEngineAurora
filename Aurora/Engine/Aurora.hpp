#pragma once


#ifndef _AURORA_HPP_
#define _AURORA_HPP_

#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<chrono>
#include<cstdlib>
#include<memory>
#include<Windows.h>
#include<wingdi.h>

#include"Music.hpp"
#include"Graphics.hpp"
#include"Keyboard.hpp"
#include"Mouse.hpp"
#include"Game.hpp"
#include"GameSceneManager.hpp"
#include"Configuration.hpp"

class Aurora
{
public:

	static Aurora& get()
	{
		return instance;
	}

	bool iniEngine(const Configuration& config);

	void iniGame(Game* game);

private:

	GLFWwindow* window;

	void run();

	Aurora() {}

	Aurora(const Aurora&) {}

	HWND get_wallpaper_window();

	static Aurora instance;

	std::shared_ptr<Game> game;

	std::chrono::steady_clock timer;

	std::chrono::steady_clock::time_point timeStart;

	std::chrono::steady_clock::time_point timeEnd;

};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

void getSysResolution(int& width, int& height);

#endif // !_AURORA_HPP_
