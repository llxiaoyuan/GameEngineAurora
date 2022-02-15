#pragma once

#include<Actor.hpp>
#include<Utility.hpp>
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

	void render() override
	{
		texture->draw();
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
			grounds.push_back(Ground(&groundTextures[rand() % 3], (float)1920 * i, (float)35));
		}
	}

	~GroundManager()
	{
		for (int i = 2; i > -1; i--)
		{
			groundTextures[i].dispose();
		}
	}

	void update(float dt)
	{
		
		for (int i = 0; i < grounds.size(); i++)
		{
			grounds[i].update(dt);
			if (grounds[i].position[0] < -1925.f)
			{
				float maxX=0;
				for (int i2 = 0; i2 < grounds.size(); i2++)
				{
					if (grounds[i2].position[0] > maxX)
					{
						maxX = grounds[i2].position[0];
					}
				}
				grounds[i].position[0] = maxX + 1920.f;
				
				grounds[i].texture = &groundTextures[rand() % 3];
			}
		}
	}

	void render(SpriteRenderer& renderer)
	{
		for (int i = 0; i < grounds.size(); i++)
		{
			renderer.draw(grounds[i]);
		}
	}

};