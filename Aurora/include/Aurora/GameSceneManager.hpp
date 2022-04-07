#pragma once

#ifndef _GAME_SCENE_MANAGER_HPP_
#define _GAME_SCENE_MANAGER_HPP_

#include<stack>
#include<type_traits>
#include<memory>

#include"SpriteRenderer.hpp"
#include"ShapeRenderer.hpp"

class GameSceneManager;

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

	virtual void render(SpriteRenderer* const spriteRenderer,ShapeRenderer* const shapeRenderer) = 0;

};

class GameSceneManager
{
public:

	static GameSceneManager* create()
	{
		return new GameSceneManager();
	}

	GameSceneManager(const GameSceneManager&) = delete;

	~GameSceneManager()
	{
		std::cout << "[class GameSceneManager] release!\n";
		while (scenes.size())
		{
			delete scenes.top();
			scenes.pop();
		}
	}

	void push(Scene* const scene)
	{
		if (!scene)
		{
			std::cout << "[class GameSceneManager] scene is nullptr!\n";
			return;
		}
		scenes.push(scene);
	}

	void pop()
	{
		if (scenes.size())
		{
			delete scenes.top();
			scenes.pop();
		}
	}

	void set(Scene* const scene)
	{
		if (scenes.size())
		{
			delete scenes.top();
			scenes.pop();
		}
		if (!scene)
		{
			std::cout << "[class GameSceneManager] scene is nullptr!\n";
			return;
		}
		scenes.push(scene);
	}

	void update(const float& dt)
	{
		scenes.top()->update(dt);
	}

	void render(SpriteRenderer* const spriteRenderer,ShapeRenderer* const shapeRenderer)
	{
		scenes.top()->render(spriteRenderer, shapeRenderer);
	}

private:

	GameSceneManager()
	{
		
	}

	std::stack<Scene*> scenes;

};

#endif // !_GAME_SCENE_MANAGER_HPP_
