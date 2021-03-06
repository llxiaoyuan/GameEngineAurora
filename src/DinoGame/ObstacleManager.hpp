#pragma once

#include<Aurora/Actor.hpp>
#include<Aurora/Random.hpp>
#include<Aurora/Rect.hpp>
#include<string>

class Obstacle :public Actor
{
public:

	Texture* texture;

	Rect rect;

	Obstacle(Texture* texture, float x, float y) :
		texture(texture)
	{
		rect = Rect(x, y, (float)texture->getWidth(), (float)texture->getHeight());
		position = glm::vec3(x, y, 0);
	}

	void update(const float& dt) override
	{
		position[0] -= 600 * dt;
		rect.setX(position[0]);
	}

	void render(SpriteRenderer* const renderer) override
	{
		renderer->draw(texture, position[0], position[1]);
	}
};

class ObstacleManager
{
public:

	Texture* obstacleTextures[6];

	std::vector<Obstacle> obstacles;

	float timeToNextSpawnCount;

	float timeToNextSpawn;

	ObstacleManager() :
		timeToNextSpawnCount(0),
		timeToNextSpawn(Random::Float() * 2.f + 1.5f)
	{
		for (int i = 0; i < 6; i++)
		{
			obstacleTextures[i] = Texture::create("res\\DinoGameRes\\textures\\Obstacle" + std::to_string(i + 1) + ".png");
		}
	}

	~ObstacleManager()
	{
		for (int i = 5; i > -1; i--)
		{
			delete obstacleTextures[i];
		}
	}

	void update(float dt)
	{
		for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
		{
			it->update(dt);
		}

		for (auto it = obstacles.begin(); it != obstacles.end(); ++it)
		{
			if (it->getX() < -130)
			{
				obstacles.erase(it);
				break;
			}
		}

		timeToNextSpawnCount += dt;

		if (timeToNextSpawnCount > timeToNextSpawn)
		{
			timeToNextSpawnCount = 0;
			timeToNextSpawn = Random::Float() * 2.f + 1.5f;
			obstacles.push_back(Obstacle(obstacleTextures[Random::Int() % 6], 1000, 50));
		}

	}

	void render(SpriteRenderer* const renderer)
	{
		for (int i = 0; i < obstacles.size(); i++)
		{
			obstacles[i].render(renderer);
		}
	}

};