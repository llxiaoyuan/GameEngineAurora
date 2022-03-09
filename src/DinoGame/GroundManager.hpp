#pragma once

#include<Aurora/Actor.hpp>
#include<Aurora/Utility.hpp>
#include<string>

class Ground :public Actor
{
public:

	Texture* texture;

	Ground(Texture* texture, float x, float y) :
		texture(texture)
	{
		position = glm::vec3(x, y, 0);
	}

	void update(const float& dt) override
	{
		position[0] -= 600 * dt;
	}

	void render(SpriteRenderer& renderer) override
	{
		renderer.draw(*texture, position[0], position[1]);
	}
};

class GroundManager
{
public:

	std::vector<Texture> groundTextures;

	std::vector<Ground> grounds;

	GroundManager()
	{
		for (int i = 0; i < 3; i++)
		{
			groundTextures.push_back(Texture("res\\DinoGameRes\\textures\\land" + std::to_string(i+1) + ".png"));
		}
		for (int i = 0; i < 3; i++)
		{
			grounds.push_back(Ground(&groundTextures[0], (float)1920 * i, (float)35));
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
			if (grounds[i].getX() < -1925.f)
			{
				float maxX=0;
				for (int i2 = 0; i2 < grounds.size(); i2++)
				{
					if (grounds[i2].getX() > maxX)
					{
						maxX = grounds[i2].getX();
					}
				}
				grounds[i].setX(maxX + 1920.f);
				grounds[i].texture = &groundTextures[0];
			}
		}
	}

	void render(SpriteRenderer& renderer)
	{
		for (int i = 0; i < grounds.size(); i++)
		{
			grounds[i].render(renderer);
		}
	}

};