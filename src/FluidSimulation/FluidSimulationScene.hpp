#pragma once

#include<Aurora/GameSceneManager.hpp>

#include"Config.hpp"
#include"DoubleFBO.hpp"
#include"Pointer.hpp"

#include<string>
#include<vector>
#include<cmath>

class FluidSimulationScene :public Scene
{
public:

	FluidSimulationScene(GameSceneManager* gsm) :
		Scene(gsm)
	{
		glGenVertexArrays(1, &blitVAO);
		glBindVertexArray(blitVAO);
		glGenBuffers(1, &blitVBO);
		glBindBuffer(GL_ARRAY_BUFFER, blitVBO);

		float positions[] = { -1, -1, -1, 1, 1, 1, 1, -1 };

		glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), positions, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)(0 * sizeof(float)));

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		std::string baseVertexShader = "res\\FluidSimulationRes\\shaders\\baseVertexShader.vert";
		std::string blurVertexShader = "res\\FluidSimulationRes\\shaders\\blurVertexShader.vert";
		std::string blurShader = "res\\FluidSimulationRes\\shaders\\blurShader.frag";
		std::string copyShader = "res\\FluidSimulationRes\\shaders\\copyShader.frag";
		std::string clearShader = "res\\FluidSimulationRes\\shaders\\clearShader.frag";
		std::string colorShader = "res\\FluidSimulationRes\\shaders\\colorShader.frag";
		std::string displayShader = "res\\FluidSimulationRes\\shaders\\displayShader.frag";
		std::string sunraysMaskShader = "res\\FluidSimulationRes\\shaders\\sunraysMaskShader.frag";
		std::string sunraysShader = "res\\FluidSimulationRes\\shaders\\sunraysShader.frag";
		std::string splatShader = "res\\FluidSimulationRes\\shaders\\splatShader.frag";
		std::string advectionShader = "res\\FluidSimulationRes\\shaders\\advectionShader.frag";
		std::string divergenceShader = "res\\FluidSimulationRes\\shaders\\divergenceShader.frag";
		std::string curlShader = "res\\FluidSimulationRes\\shaders\\curlShader.frag";
		std::string vorticityShader = "res\\FluidSimulationRes\\shaders\\vorticityShader.frag";
		std::string pressureShader = "res\\FluidSimulationRes\\shaders\\pressureShader.frag";
		std::string gradientSubtractShader = "res\\FluidSimulationRes\\shaders\\gradientSubtractShader.frag";

		blurProgram = Shader::create(blurVertexShader, blurShader);
		copyProgram = Shader::create(baseVertexShader, copyShader);
		clearProgram = Shader::create(baseVertexShader, clearShader);
		colorProgram = Shader::create(baseVertexShader, colorShader);
		sunraysMaskProgram = Shader::create(baseVertexShader, sunraysMaskShader);
		sunraysProgram = Shader::create(baseVertexShader, sunraysShader);
		splatProgram = Shader::create(baseVertexShader, splatShader);
		advectionProgram = Shader::create(baseVertexShader, advectionShader);
		divergenceProgram = Shader::create(baseVertexShader, divergenceShader);
		curlProgram = Shader::create(baseVertexShader, curlShader);
		vorticityProgram = Shader::create(baseVertexShader, vorticityShader);
		pressureProgram = Shader::create(baseVertexShader, pressureShader);
		gradienSubtractProgram = Shader::create(baseVertexShader, gradientSubtractShader);
		displayProgram = Shader::create(baseVertexShader, displayShader);

		{
			Resolution simRes = getResolution(config.SIM_RESOLUTION);
			Resolution dyeRes = getResolution(config.DYE_RESOLUTION);

			unsigned int texType = GL_HALF_FLOAT;

			PixelFormat rgba = { GL_RGBA16F,GL_RGBA };
			PixelFormat rg = { GL_RG16F,GL_RG };
			PixelFormat r = { GL_R16F,GL_RED };

			dye = new DoubleFBO(dyeRes.width, dyeRes.height, rgba.internalFormat, rgba.format, texType, GL_LINEAR);

			velocity = new DoubleFBO(simRes.width, simRes.height, rg.internalFormat, rg.format, texType, GL_LINEAR);

			divergence = GL::createFBO(simRes.width, simRes.height, r.internalFormat, r.format, texType, GL_NEAREST);
			curl = GL::createFBO(simRes.width, simRes.height, r.internalFormat, r.format, texType, GL_NEAREST);
			pressure = new DoubleFBO(simRes.width, simRes.height, r.internalFormat, r.format, texType, GL_NEAREST);
		}

		{
			Resolution res = getResolution(config.SUNRAYS_RESOLUTION);

			unsigned int texType = GL_HALF_FLOAT;

			PixelFormat r = { GL_R16F,GL_RED };

			sunrays = GL::createFBO(res.width, res.height, r.internalFormat, r.format, texType, GL_LINEAR);
			sunraysTemp = GL::createFBO(res.width, res.height, r.internalFormat, r.format, texType, GL_LINEAR);
		}

		pointer = new Pointer();

		Mouse::addLeftDownEvent(this, &FluidSimulationScene::leftDownEvent);
		Mouse::addLeftUpEvent(this, &FluidSimulationScene::leftUpEvent);
		Mouse::addMoveEvent(this, &FluidSimulationScene::moveEvent);
	}

	~FluidSimulationScene()
	{
		glDeleteVertexArrays(1, &blitVAO);
		glDeleteBuffers(1, &blitVBO);

		delete blurProgram;
		delete copyProgram;
		delete clearProgram;
		delete colorProgram;
		delete sunraysMaskProgram;
		delete sunraysProgram;
		delete splatProgram;
		delete advectionProgram;
		delete divergenceProgram;
		delete curlProgram;
		delete vorticityProgram;
		delete pressureProgram;
		delete gradienSubtractProgram;
		delete displayProgram;

		delete pointer;

		if (dye)
		{
			delete dye;
		}

		if (velocity)
		{
			delete velocity;
		}

		if (pressure)
		{
			delete pressure;
		}

		if (divergence)
		{
			delete divergence;
		}

		if (curl)
		{
			delete curl;
		}

		if (sunrays)
		{
			delete sunrays;
		}

		if (sunraysTemp)
		{
			delete sunraysTemp;
		}

	}

	void leftDownEvent()
	{
		int posX = Mouse::getPosition().x;
		int posY = Mouse::getPosition().y;
		updatePointerDownData(-1, posX, Graphics::getHeight() - posY);
	}

	void leftUpEvent()
	{
		updatePointerUpData();
	}

	void moveEvent()
	{
		if (pointer->down)
		{
			int posX = Mouse::getPosition().x;
			int posY = Mouse::getPosition().y;
			updatePointerMoveData(posX, Graphics::getHeight() - posY);
		}
	}

	void handleinput() override
	{

	}

	void update(const float& dt) override
	{
		updateColors(dt);
		applyInputs();
		step(dt);
	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override
	{
		applySunrays(dye->read(), dye->write(), sunrays);
		blur(sunrays, sunraysTemp, 1);

		glBlendFunc(GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
		glEnable(GL_BLEND);

		int width = Graphics::getWidth();
		int height = Graphics::getHeight();

		glViewport(0, 0, width, height);

		drawColor(ColorRGB{ 0,0,0 });

		drawDisplay(width, height);
	}

private:

	void blit(const unsigned int& fbo)
	{
		glBindVertexArray(blitVAO);
		glBindFramebuffer(GL_FRAMEBUFFER, fbo);
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(0);
	}

	void updateColors(const float& dt)
	{
		colorUpdateTimer += dt * config.COLOR_UPDATE_SPEED;
		if (colorUpdateTimer >= 1.f)
		{
			colorUpdateTimer = 0;
			pointer->makeColorRandom();
		}
	}

	void step(const float& dt)
	{
		glDisable(GL_BLEND);
		glViewport(0, 0, velocity->width, velocity->height);

		curlProgram->bind();
		glUniform2f(curlProgram->uniforms["texelSize"], velocity->texelSizeX, velocity->texelSizeY);
		glUniform1i(curlProgram->uniforms["uVelocity"], velocity->read()->attachTexture(0));
		blit(curl->fbo);

		vorticityProgram->bind();
		glUniform2f(vorticityProgram->uniforms["texelSize"], velocity->texelSizeX, velocity->texelSizeY);
		glUniform1i(vorticityProgram->uniforms["uVelocity"], velocity->read()->attachTexture(0));
		glUniform1i(vorticityProgram->uniforms["uCurl"], curl->attachTexture(1));
		glUniform1f(vorticityProgram->uniforms["curl"], config.CURL);
		glUniform1f(vorticityProgram->uniforms["dt"], dt);
		blit(velocity->write()->fbo);
		velocity->swap();

		divergenceProgram->bind();
		glUniform2f(divergenceProgram->uniforms["texelSize"], velocity->texelSizeX, velocity->texelSizeY);
		glUniform1i(divergenceProgram->uniforms["uVelocity"], velocity->read()->attachTexture(0));
		blit(divergence->fbo);

		clearProgram->bind();
		glUniform1i(clearProgram->uniforms["uTexture"], pressure->read()->attachTexture(0));
		glUniform1f(clearProgram->uniforms["value"], config.PRESSURE);
		blit(pressure->write()->fbo);
		pressure->swap();

		pressureProgram->bind();
		glUniform2f(pressureProgram->uniforms["texelSize"], velocity->texelSizeX, velocity->texelSizeY);
		glUniform1i(pressureProgram->uniforms["uDivergence"], divergence->attachTexture(0));
		for (int i = 0; i < config.PRESSURE_ITERATIONS; i++)
		{
			glUniform1i(pressureProgram->uniforms["uPressure"], pressure->read()->attachTexture(1));
			blit(pressure->write()->fbo);
			pressure->swap();
		}

		gradienSubtractProgram->bind();
		glUniform2f(gradienSubtractProgram->uniforms["texelSize"], velocity->texelSizeX, velocity->texelSizeY);
		glUniform1i(gradienSubtractProgram->uniforms["uPressure"], pressure->read()->attachTexture(0));
		glUniform1i(gradienSubtractProgram->uniforms["uVelocity"], velocity->read()->attachTexture(1));
		blit(velocity->write()->fbo);
		velocity->swap();

		advectionProgram->bind();
		glUniform2f(advectionProgram->uniforms["texelSize"], velocity->texelSizeX, velocity->texelSizeY);
		int velocityId = velocity->read()->attachTexture(0);
		glUniform1i(advectionProgram->uniforms["uVelocity"], velocityId);
		glUniform1i(advectionProgram->uniforms["uSource"], velocityId);
		glUniform1f(advectionProgram->uniforms["dt"], dt);
		glUniform1f(advectionProgram->uniforms["dissipation"], config.VELOCITY_DISSIPATION);
		blit(velocity->write()->fbo);
		velocity->swap();

		glViewport(0, 0, dye->width, dye->height);

		glUniform1i(advectionProgram->uniforms["uVelocity"], velocity->read()->attachTexture(0));
		glUniform1i(advectionProgram->uniforms["uSource"], dye->read()->attachTexture(1));
		glUniform1f(advectionProgram->uniforms["dissipation"], config.DENSITY_DISSIPATION);
		blit(dye->write()->fbo);
		dye->swap();

	}

	void drawColor(const ColorRGB& color)
	{
		colorProgram->bind();
		glUniform4f(colorProgram->uniforms["color"], color.r, color.g, color.b, 1);
		blit(0);
	}

	void drawDisplay(const int& width, const int& height)
	{
		displayProgram->bind();
		glUniform2f(displayProgram->uniforms["texelSize"], 1.0f / width, 1.0f / height);
		glUniform1i(displayProgram->uniforms["uTexture"], dye->read()->attachTexture(0));
		glUniform1i(displayProgram->uniforms["uSunrays"], sunrays->attachTexture(3));
		blit(0);
	}

	void applySunrays(FBO* const source, FBO* const mask, FBO* const destination)
	{
		glDisable(GL_BLEND);
		sunraysMaskProgram->bind();
		glUniform1i(sunraysMaskProgram->uniforms["uTexture"], source->attachTexture(0));
		glViewport(0, 0, mask->width, mask->height);
		blit(mask->fbo);

		sunraysProgram->bind();
		glUniform1f(sunraysProgram->uniforms["weight"], config.SUNRAYS_WEIGHT);
		glUniform1i(sunraysProgram->uniforms["uTexture"], mask->attachTexture(0));
		glViewport(0, 0, destination->width, destination->height);
		blit(destination->fbo);
	}

	void blur(FBO* const target, FBO* const temp, const int& iterations)
	{
		blurProgram->bind();
		for (int i = 0; i < iterations; i++)
		{
			glUniform2f(blurProgram->uniforms["texelSize"], target->texelSizeX, 0.0);
			glUniform1i(blurProgram->uniforms["uTexture"], target->attachTexture(0));
			blit(temp->fbo);

			glUniform2f(blurProgram->uniforms["texelSize"], 0.0, target->texelSizeY);
			glUniform1i(blurProgram->uniforms["uTexture"], temp->attachTexture(0));
			blit(target->fbo);
		}
	}

	void applyInputs()
	{
		if (pointer->moved)
		{
			pointer->moved = false;
			splatPointer(pointer);
		}
	}

	void splatPointer(Pointer* const pointer)
	{
		const float dx = pointer->deltaX * config.SPLAT_FORCE;
		const float dy = pointer->deltaY * config.SPLAT_FORCE;
		splat(pointer->texcoordX, pointer->texcoordY, dx, dy, pointer->r, pointer->g, pointer->b);
	}

	void splat(const float& x, const float& y, const float& dx, const float& dy, const float& r, const float& g, const float& b)
	{
		glViewport(0, 0, velocity->width, velocity->height);
		splatProgram->bind();
		glUniform1i(splatProgram->uniforms["uTarget"], velocity->read()->attachTexture(0));
		glUniform1f(splatProgram->uniforms["aspectRatio"], (float)Graphics::getWidth() / Graphics::getHeight());
		glUniform2f(splatProgram->uniforms["point"], x, y);
		glUniform3f(splatProgram->uniforms["color"], dx, dy, 0.f);
		glUniform1f(splatProgram->uniforms["radius"], correctRadius(config.SPLAT_RADIUS / 100.0f));
		blit(velocity->write()->fbo);
		velocity->swap();

		glViewport(0, 0, dye->width, dye->height);
		glUniform1i(splatProgram->uniforms["uTarget"], dye->read()->attachTexture(0));
		glUniform3f(splatProgram->uniforms["color"], r, g, b);
		blit(dye->write()->fbo);
		dye->swap();
	}

	float correctRadius(float radius)
	{
		const float aspectRatio = (float)Graphics::getWidth() / Graphics::getHeight();
		radius *= aspectRatio;
		return radius;
	}

	void updatePointerDownData(const int& id, const float& posX, const float& posY)
	{
		pointer->id = id;
		pointer->down = true;
		pointer->moved = false;
		pointer->texcoordX = posX / Graphics::getWidth();
		pointer->texcoordY = 1.0f - posY / Graphics::getHeight();
		pointer->prevTexcoordX = pointer->texcoordX;
		pointer->prevTexcoordY = pointer->texcoordY;
		pointer->deltaX = 0;
		pointer->deltaY = 0;
		pointer->makeColorRandom();
	}

	void updatePointerMoveData(const float& posX, const float& posY)
	{
		pointer->prevTexcoordX = pointer->texcoordX;
		pointer->prevTexcoordY = pointer->texcoordY;
		pointer->texcoordX = posX / Graphics::getWidth();
		pointer->texcoordY = 1.0f - posY / Graphics::getHeight();
		pointer->deltaX = pointer->texcoordX - pointer->prevTexcoordX;
		pointer->deltaY = correctDeltaY(pointer->texcoordY - pointer->prevTexcoordY);
		pointer->moved = fabsf(pointer->deltaX) > 0 || fabsf(pointer->deltaY) > 0;
	}

	void updatePointerUpData()
	{
		pointer->down = false;
	}

	float correctDeltaY(float delta)
	{
		const float aspectRatio = (float)Graphics::getWidth() / Graphics::getHeight();
		delta /= aspectRatio;
		return delta;
	}

	float colorUpdateTimer = 0.0f;

	const Config config;

	unsigned int blitVAO;

	unsigned int blitVBO;

	Shader* blurProgram; ;
	Shader* copyProgram;
	Shader* clearProgram;
	Shader* colorProgram;
	Shader* sunraysMaskProgram;
	Shader* sunraysProgram;
	Shader* splatProgram;
	Shader* advectionProgram;
	Shader* divergenceProgram;
	Shader* curlProgram;
	Shader* vorticityProgram;
	Shader* pressureProgram;
	Shader* gradienSubtractProgram;
	Shader* displayProgram;

	Pointer* pointer;

	DoubleFBO* dye;
	DoubleFBO* velocity;
	DoubleFBO* pressure;

	FBO* divergence;
	FBO* curl;
	FBO* sunrays;
	FBO* sunraysTemp;

};