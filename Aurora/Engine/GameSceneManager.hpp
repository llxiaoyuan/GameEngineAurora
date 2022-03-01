#pragma once

#ifndef _GAME_SCENE_MANAGER_HPP_
#define _GAME_SCENE_MANAGER_HPP_

#include<vector>
#include<type_traits>

#include"SpriteRenderer.hpp"

class GameSceneManager;
class SpriteRenderer;

class Scene
{
public:

	GameSceneManager* gsm;

	Scene(GameSceneManager* manager) :
		gsm(manager)
	{

	}

	virtual ~Scene() {}

	virtual std::shared_ptr<Scene> clone() = 0;

	virtual void handleinput() = 0;

	virtual void update(const float& dt) = 0;

	virtual void render(SpriteRenderer& renderer) = 0;

};

class GameSceneManager
{
public:

	GameSceneManager()
	{

	}

	~GameSceneManager()
	{
		std::cout << "[" << typeid(*this).name() << "] release!\n";
	}

	void push(Scene* scene)
	{
		scenes.push_back(scene->clone());
	}

	void pop()
	{
		scenes.pop_back();
	}

	void set(Scene* scene)
	{
		scenes.pop_back();
		scenes.push_back(scene->clone());
	}

	void update(const float& dt)
	{
		scenes.back()->update(dt);
	}

	void render(SpriteRenderer& renderer)
	{
		scenes.back()->render(renderer);
	}

private:

	std::vector<std::shared_ptr<Scene>> scenes;

};

#endif // !_GAME_SCENE_MANAGER_HPP_
