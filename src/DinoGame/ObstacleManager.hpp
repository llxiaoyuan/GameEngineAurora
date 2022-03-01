#pragma once

#include<Actor.hpp>
#include<Utility.hpp>
#include<string>
#include<Rectangle.hpp>

class Obstacle :public Actor
{
public:

	Texture* texture;

	Rectangle rect;

	Obstacle(Texture* texture, float x, float y) :
		texture(texture)
	{
		rect = Rectangle(x, y, (float)texture->getWidth(), (float)texture->getHeight());
		position = glm::vec3(x, y, 0);
	}

	void update(const float& dt) override
	{
		position[0] -= 600 * dt;
		rect.setX(position[0]);
	}

	void render() override
	{
		texture->draw();
	}
};

class ObstacleManager
{
public:

	std::vector<Texture> obstacleTextures;

	std::vector<Obstacle> obstacles;

	float timeToNextSpawnCount;

	float timeToNextSpawn;

	ObstacleManager() :
		timeToNextSpawnCount(0),
		timeToNextSpawn(Utility::rFloat() * 2.f + 1.5f)
	{
		for (int i = 0; i < 6; i++)
		{
			obstacleTextures.push_back(Texture("res\\DinoGameRes\\textures\\Obstacle" + std::to_string(i + 1) + ".png"));
		}
	}

	~ObstacleManager()
	{
		for (int i = 5; i > -1; i--)
		{
			obstacleTextures[i].dispose();
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
			timeToNextSpawn = Utility::rFloat() * 2.f + 1.5f;
			obstacles.push_back(Obstacle(&obstacleTextures[rand() % 6], 1000, 50));
		}

	}

	void render(SpriteRenderer& renderer)
	{
		for (int i = 0; i < obstacles.size(); i++)
		{
			renderer.draw(obstacles[i]);
		}
	}

};