#pragma once


#ifndef _AURORA_HPP_
#define _AURORA_HPP_

#include <windows.h>
#include<chrono>

#include<glad/glad.h>
#include<GLFW/glfw3.h>

#include"VideoRecorder.hpp"
#include"Sound.hpp"
#include"Graphics.hpp"
#include"Keyboard.hpp"
#include"Mouse.hpp"
#include"Game.hpp"
#include"Configuration.hpp"
#include"Random.hpp"

class Aurora
{
public:

	void operator=(const Aurora&) = delete;

	static Aurora& get()
	{
		return instance;
	}

	bool iniEngine(const Configuration& configuration);

	void iniGame(Game* const game);

private:

	GLFWwindow* window;

	void runGame();

	void runWallpaper();

	void runRecord();

	Aurora() :window(nullptr), config(nullptr) ,game(nullptr) {}

	Aurora(const Aurora&) :window(nullptr), config(nullptr), game(nullptr) {}

	static Aurora instance;

	Game* game;

	const Configuration* config;

	std::chrono::steady_clock timer;

	std::chrono::steady_clock::time_point timeStart;

	std::chrono::steady_clock::time_point timeEnd;

};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

HWND get_wallpaper_window();

void getSysResolution(int& width, int& height);

#endif // !_AURORA_HPP_