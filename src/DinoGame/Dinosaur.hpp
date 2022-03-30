#pragma once

#include<Aurora/Actor.hpp>
#include<Aurora/Keyboard.hpp>
#include<Aurora/Rect.hpp>
#include<Aurora/Animation.hpp>
#include<Aurora/Mouse.hpp>

class Dinosaur :public Actor
{
public:

	Rect rect;

	Animation* runAnimation;
	Texture* collideTexture;
	Texture* jumpingTexture;

	bool isJumping;
	bool collided;

	float runStateTime;

	Sound* jumpSound;

	const float gravityConst;

	glm::vec3 speed;

	Dinosaur():
		runAnimation(Animation::create(0.07f)),
		speed(glm::vec3(0,0,0)),
		gravityConst(3000),
		isJumping(false),
		collided(false),
		runStateTime(0),
		jumpSound(Sound::create("res\\DinoGameRes\\music\\jump.mp3", false))
	{
		std::vector<Texture*> buffers(Texture::loadSplit("res\\DinoGameRes\\textures\\DinosaurP.png", 70, 75, 4));
		collideTexture=buffers[0];
		jumpingTexture=buffers[1];
		rect = Rect(100, 50, 50, 65);
		position = glm::vec3(100, 50, 0);
		runAnimation->addTexture(buffers[2]);
		runAnimation->addTexture(buffers[3]);

		Keyboard::addKeyPressEvent(Keyboard::Space, this, &Dinosaur::jump);
	}

	~Dinosaur()
	{
		delete collideTexture;
		delete jumpingTexture;
		delete runAnimation;
		delete jumpSound;
	}

	void handleinput()
	{
		/*if (Keyboard::getKeyPress(Keyboard::Space))
		{
			jump();
		}*/
	}

	void jump()
	{
		if (!isJumping)
		{
			jumpSound->play();
			isJumping = true;
			speed += glm::vec3(0, 1000, 0);
		}
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

	void render(SpriteRenderer* const renderer) override
	{
		if (collided)
		{
			renderer->draw(collideTexture, position[0], position[1]);
		}
		else
		{
			if (isJumping)
			{
				renderer->draw(jumpingTexture, position[0], position[1]);
			}
			else
			{
				renderer->draw(runAnimation->getTexture(runStateTime), position[0], position[1]);
			}
		}
	}
	
};