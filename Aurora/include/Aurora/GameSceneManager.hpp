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
	}

	template<typename Obj>
	void push(Obj obj)
	{
		scenes.push(std::make_unique<std::remove_reference<decltype(*obj)>::type>(*obj));
	}

	void pop()
	{
		scenes.pop();
	}

	template<typename Obj>
	void set(Obj obj)
	{
		scenes.pop();
		scenes.push(std::make_unique<std::remove_reference<decltype(*obj)>::type>(*obj));
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

	std::stack<std::unique_ptr<Scene>> scenes;

};

#endif // !_GAME_SCENE_MANAGER_HPP_
