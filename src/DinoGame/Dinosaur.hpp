#pragma once

#include<Actor.hpp>
#include<Keyboard.hpp>
#include<Rectangle.hpp>
#include<Animation.hpp>
#include<Mouse.hpp>

class Dinosaur :public Actor
{
public:

	Rectangle rect;

	Animation runAnimation;
	Texture collideTexture;
	Texture jumpingTexture;

	bool isJumping;
	bool collided;

	float runStateTime;

	const float gravityConst;

	glm::vec3 speed;

	Dinosaur():
		runAnimation(0.07f),
		speed(glm::vec3(0,0,0)),
		gravityConst(3000),
		isJumping(false),
		collided(false),
		runStateTime(0)
	{
		std::vector<Texture> buffers(Texture::loadSplit("res\\DinoGameRes\\textures\\DinosaurP.png", 70, 75, 4));
		collideTexture=Texture(buffers[0]);
		jumpingTexture=Texture(buffers[1]);
		rect = Rectangle(100, 50, 50, 65);
		position = glm::vec3(100, 50, 0);
		runAnimation.addTexture(buffers[2]);
		runAnimation.addTexture(buffers[3]);
	}

	~Dinosaur()
	{
		collideTexture.dispose();
		jumpingTexture.dispose();
	}

	void handleinput()
	{
		if (Mouse::isLeftDown())
		{
			if (!isJumping)
			{
				Music::play("res\\DinoGameRes\\music\\jump.mp3", false);
				jump();
			}
		}
	}

	void jump()
	{
		isJumping = true;
		speed += glm::vec3(0, 1000, 0);
	}

	void update(const float& dt) override
	{
		handleinput();
		if (isJumping)
		{
			speed -= glm::vec3(0, gravityConst, 0) * dt;
			position += speed * dt;
			rect.setY(position[1]);
			if (position[1] < 50)
			{
				isJumping = false;
				speed[1] = 0;
				position[1] = 50;
				rect.setY(50);
			}
		}
		else
		{
			runStateTime += dt;
		}
	}

	void render() override
	{
		if (collided)
		{
			collideTexture.draw();
		}
		else
		{
			if (isJumping)
			{
				jumpingTexture.draw();
			}
			else
			{
				runAnimation.getTexture(runStateTime).draw();
			}
		}
	}
	
};