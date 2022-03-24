#pragma once

#include<Aurora/ParticleSystem.hpp>

class MyParticleSystem :public ParticleSystem
{
public:

	MyParticleSystem():
		ParticleSystem(2.f, 20000)
	{
		glm::vec2 startPos(particleSize / 2, particleSize / 2);
		for (int i = 0; i < maxParticleNumber; i++)
		{
			particles[i].avtive = true;
			int x = i % (Graphics::getWidth() / (int)particleSize);
			int y = i / (Graphics::getWidth() / (int)particleSize);
			particles[i].pos = glm::vec2(x * particleSize, y * particleSize) + startPos;
			particles[i].color = glm::vec4(Random::Float(), Random::Float(), Random::Float(), 1);
		}
		colors[0] = glm::vec4(0.027451, 0.027451, 0.027451, 0);
		colors[1] = glm::vec4(0.121569, 0.027451, 0.027451, 0);
		colors[2] = glm::vec4(0.184314, 0.0588235, 0.027451, 1);
		colors[3] = glm::vec4(0.278431, 0.0588235, 0.027451, 1);
		colors[4] = glm::vec4(0.341176, 0.0901961, 0.027451, 1);
		colors[5] = glm::vec4(0.403922, 0.121569, 0.027451, 1);
		colors[6] = glm::vec4(0.466667, 0.121569, 0.027451, 1);
		colors[7] = glm::vec4(0.560784, 0.152941, 0.027451, 1);
		colors[8] = glm::vec4(0.623529, 0.184314, 0.027451, 1);
		colors[9] = glm::vec4(0.686275, 0.247059, 0.027451, 1);
		colors[10] = glm::vec4(0.74902, 0.278431, 0.027451, 1);
		colors[11] = glm::vec4(0.780392, 0.278431, 0.027451, 1);
		colors[12] = glm::vec4(0.87451, 0.309804, 0.027451, 1);
		colors[13] = glm::vec4(0.87451, 0.341176, 0.027451, 1);
		colors[14] = glm::vec4(0.87451, 0.341176, 0.027451, 1);
		colors[15] = glm::vec4(0.843137, 0.372549, 0.027451, 1);
		colors[16] = glm::vec4(0.843137, 0.372549, 0.027451, 1);
		colors[17] = glm::vec4(0.843137, 0.403922, 0.0588235, 1);
		colors[18] = glm::vec4(0.811765, 0.435294, 0.0588235, 1);
		colors[19] = glm::vec4(0.811765, 0.466667, 0.0588235, 1);
		colors[20] = glm::vec4(0.811765, 0.498039, 0.0588235, 1);
		colors[21] = glm::vec4(0.811765, 0.529412, 0.0901961, 1);
		colors[22] = glm::vec4(0.780392, 0.529412, 0.0901961, 1);
		colors[23] = glm::vec4(0.780392, 0.560784, 0.0901961, 1);
		colors[24] = glm::vec4(0.780392, 0.592157, 0.121569, 1);
		colors[25] = glm::vec4(0.74902, 0.623529, 0.121569, 1);
		colors[26] = glm::vec4(0.74902, 0.623529, 0.121569, 1);
		colors[27] = glm::vec4(0.74902, 0.654902, 0.152941, 1);
		colors[28] = glm::vec4(0.74902, 0.654902, 0.152941, 1);
		colors[29] = glm::vec4(0.74902, 0.686275, 0.184314, 1);
		colors[30] = glm::vec4(0.717647, 0.686275, 0.184314, 1);
		colors[31] = glm::vec4(0.717647, 0.717647, 0.184314, 1);
		colors[32] = glm::vec4(0.717647, 0.717647, 0.215686, 1);
		colors[33] = glm::vec4(0.811765, 0.811765, 0.435294, 1);
		colors[34] = glm::vec4(0.87451, 0.87451, 0.623529, 1);
		colors[35] = glm::vec4(0.937255, 0.937255, 0.780392, 1);
		colors[36] = glm::vec4(1, 1, 1, 1);

		for (int i = 0; i < Graphics::getWidth() / (int)particleSize; i++)
		{
			indices[i] = 36;
		}
	}

	glm::vec4 colors[37];

	int indices[20000] = {0};

	float sumTime = 0;

	void update(const float& dt) override
	{
		for (int i = 0; i < maxParticleNumber; i++)
		{
			spreadFire(i);
		}

		for (int i = 0; i < maxParticleNumber; i++)
		{
			particles[i].color = colors[indices[i]];
		}

		sumTime += dt;
		if (sumTime < 10.f)
		{
			for (int i = 0; i < Graphics::getWidth() / (int)particleSize; i++)
			{
				if (++indices[i] == 37)
				{
					indices[i] = 36;
				}
			}
		}
		else
		{
			for (int i = 0; i <  Graphics::getWidth() / (int)particleSize; i++)
			{
				if (--indices[i] == -1)
				{
					indices[i] = 0;
				}
			}
		}
	}

	void spreadFire(const int& from)
	{
		const int rand = (int)round(Random::Float() * 3.f) & 3;

		const int to = from + (Graphics::getWidth() / (int)particleSize) + rand - 1;

		if (to >= maxParticleNumber)
		{
			return;
		}

		int targetValue = indices[from] - (rand & 1);

		if (targetValue < 0)
		{
			targetValue = 0;
		}

		indices[to] = targetValue;
	}

};