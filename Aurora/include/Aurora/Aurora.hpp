#pragma once


#ifndef _AURORA_HPP_
#define _AURORA_HPP_

#include <windows.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<chrono>
#include<cstdlib>
#include<memory>

#include"VideoRecorder.hpp"
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

	//初始化引擎
	bool iniEngine(const Configuration& configuration);

	//初始化游戏
	void iniGame(Game* game);

private:

	GLFWwindow* window;

	//游戏循环
	void runGame();

	void runWallpaper();

	void runRecord();

	Aurora() :window(nullptr) {}

	Aurora(const Aurora&) :window(nullptr) {}

	static Aurora instance;

	std::shared_ptr<Game> game;

	const Configuration* config;

	std::chrono::steady_clock timer;

	std::chrono::steady_clock::time_point timeStart;

	std::chrono::steady_clock::time_point timeEnd;

};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

HWND get_wallpaper_window();

void getSysResolution(int& width, int& height);

#endif // !_AURORA_HPP_
