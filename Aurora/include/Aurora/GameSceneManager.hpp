#pragma once

#ifndef _GAME_SCENE_MANAGER_HPP_
#define _GAME_SCENE_MANAGER_HPP_

#include<vector>
#include<type_traits>

#include"SpriteRenderer.hpp"
#include"ShapeRenderer.hpp"

class GameSceneManager;
class SpriteRenderer;
class ShapeRenderer;

//场景
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

	//处理输入
	virtual void handleinput() = 0;

	//更新
	virtual void update(const float& dt) = 0;

	//渲染
	virtual void render(SpriteRenderer& spriteRenderer,ShapeRenderer& shapeRenderer) = 0;

};

//游戏场景管理器
class GameSceneManager
{
public:

	GameSceneManager()
	{

	}

	~GameSceneManager()
	{
		std::cout << "[class GameSceneManager] release!\n";
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

	void render(SpriteRenderer& spriteRenderer,ShapeRenderer& shapeRenderer)
	{
		scenes.back()->render(spriteRenderer, shapeRenderer);
	}

private:

	std::vector<std::shared_ptr<Scene>> scenes;

};

#endif // !_GAME_SCENE_MANAGER_HPP_
