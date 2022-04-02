#pragma once


#ifndef _AURORA_HPP_
#define _AURORA_HPP_

#include <windows.h>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
#include<chrono>
#include<memory>

#include"VideoRecorder.hpp"
#include"Sound.hpp"
#include"Graphics.hpp"
#include"Keyboard.hpp"
#include"Mouse.hpp"
#include"Game.hpp"
#include"GameSceneManager.hpp"
#include"Configuration.hpp"
#include"Random.hpp"

class Aurora
{
public:

	static Aurora& get()
	{
		return instance;
	}

	bool iniEngine(const Configuration& configuration);

	template<typename Obj>
	void iniGame(Obj obj);

private:

	GLFWwindow* window;

	void runGame();

	void runWallpaper();

	void runRecord();

	Aurora() :window(nullptr), config(nullptr) {}

	Aurora(const Aurora&) :window(nullptr), config(nullptr) {}

	static Aurora instance;

	std::unique_ptr<Game> game;

	const Configuration* config;

	std::chrono::steady_clock timer;

	std::chrono::steady_clock::time_point timeStart;

	std::chrono::steady_clock::time_point timeEnd;

};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam);

HWND get_wallpaper_window();

void getSysResolution(int& width, int& height);

template<typename Obj>
inline void Aurora::iniGame(Obj obj)
{
	this->game = std::make_unique<std::remove_reference<decltype(*obj)>::type>(*obj);
	switch (config->mode)
	{
	case Configuration::DisplayMode::Normal:
		glfwSetKeyCallback(window, key_callback);
		glfwSetCursorPosCallback(window, cursor_position_callback);
		glfwSetMouseButtonCallback(window, mouse_button_callback);
		runGame();
		break;
	case Configuration::DisplayMode::Wallpaper:
		runWallpaper();
		break;
	case Configuration::DisplayMode::Record:
		runRecord();
		break;
	default:
		break;
	}

	this->game = nullptr;

	if (config->useAudio)
	{
		Sound::release();
	}
}

#endif // !_AURORA_HPP_