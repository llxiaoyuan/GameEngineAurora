#pragma once

#include<Aurora/Actor.hpp>
#include<Aurora/Utility.hpp>
#include<string>

class Ground
{
public:

	int index;

	Ground(int index, float x, float y) :
		index(index)
	{
		position = glm::vec3(x, y, 0);
	}

	void update(const float& dt)
	{
		position.x -= 600.f * dt;
	}

	glm::vec3 position;
};

class GroundManager
{
public:

	Texture groundTextures[3];

	std::vector<Ground> grounds;

	GroundManager()
	{
		for (int i = 0; i < 3; i++)
		{
			groundTextures[i] = Texture("res\\DinoGameRes\\textures\\land" + std::to_string(i + 1) + ".png");
		}

		for (int i = 0; i < 2; i++)
		{
			int nextIndex = rand() % 3;
			grounds.emplace_back(Ground(nextIndex, (float)1920 * i, (float)35));
		}
	}

	~GroundManager()
	{
		for (int i = 0; i < 3; i++)
		{
			groundTextures[i].dispose();
		}
	}

	void update(float dt)
	{
		for (int i = 0; i < grounds.size(); i++)
		{
			grounds[i].update(dt);
			if (grounds[i].position.x < -1925.f)
			{
				float maxX = grounds[i].position.x;
				for (int i2 = 0; i2 < grounds.size(); i2++)
				{
					if (grounds[i2].position.x > maxX)
					{
						maxX = grounds[i2].position.x;
					}
				}
				int nextIndex = rand() % 3;
				grounds[i].position.x = maxX + groundTextures[1].getWidth();

				grounds[i].index = nextIndex;

			}
		}
	}

	void render(SpriteRenderer& renderer)
	{
		for (int i = 0; i < grounds.size(); i++)
		{
			renderer.draw(groundTextures[grounds[i].index], grounds[i].position.x, grounds[i].position.y);
		}
	}

};