#pragma once

#include<Aurora/Actor.hpp>
#include<Aurora/Utility.hpp>

class Cloud :public Actor
{
public:

	Texture* texture;

	Cloud(Texture* texture, float x, float y) :
		texture(texture)
	{
		position = glm::vec3(x, y, 0);
	}

	void update(const float& dt) override
	{
		position.x -= 120 * dt;
	}

	void render(SpriteRenderer* const renderer) override
	{
		renderer->draw(texture, position.x, position.y);
	}
};

class CloudManager
{
public:

	Texture* cloudTexture;

	std::vector<Cloud> clouds;

	float timeToNextSpawnCount;

	float timeToNextSpawn;

	CloudManager():
		timeToNextSpawn(Utility::rFloat()*3+1.f),
		timeToNextSpawnCount(0),
		cloudTexture(Texture::createFromFile("res\\DinoGameRes\\textures\\cloud.png"))
	{

	}

	~CloudManager()
	{
		delete cloudTexture;
	}

	void update(float dt)
	{
		timeToNextSpawnCount += dt;

		if (timeToNextSpawnCount > timeToNextSpawn)
		{
			timeToNextSpawnCount = 0;
			timeToNextSpawn = Utility::rFloat() * 9 + 1.f;
			clouds.push_back(Cloud(cloudTexture, 1000, 140 + Utility::rFloat() * 350));
		}

		for (int i = 0; i < clouds.size(); i++)
		{
			clouds[i].update(dt);
		}
	}

	void render(SpriteRenderer* const renderer)
	{
		for (int i = 0; i < clouds.size(); i++)
		{
			clouds[i].render(renderer);
		}
	}

};