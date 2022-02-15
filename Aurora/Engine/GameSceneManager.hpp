#pragma once

#ifndef _GAME_SCENE_MANAGER_HPP_
#define _GAME_SCENE_MANAGER_HPP_

#include<vector>

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
		for (int i = 0; i < scenes.size(); i++)
		{
			delete scenes[i];
		}
	}

	void push(Scene* scene)
	{
		scenes.push_back(scene);
	}

	void pop()
	{
		if (scenes.size() != 0)
		{
			delete scenes[scenes.size() - 1];
		}
		scenes.pop_back();
	}

	void set(Scene* scene)
	{
		if (scenes.size() != 0)
		{
			delete scenes[scenes.size() - 1];
		}
		scenes.pop_back();
		scenes.push_back(scene);
	}

	void update(const float& dt)
	{
		scenes[scenes.size() - 1ULL]->update(dt);
	}

	void render(SpriteRenderer& renderer)
	{
		scenes[scenes.size() - 1ULL]->render(renderer);
	}

private:

	std::vector<Scene*> scenes;

};

#endif // !_GAME_SCENE_MANAGER_HPP_
