#pragma once

#include<Aurora/GameSceneManager.hpp>

#include"Config.hpp"
#include"DoubleFBO.hpp"
#include"pointerPrototype.hpp"

#include<string>
#include<vector>

class FluidSimulationScene :public Scene
{
public:

	FluidSimulationScene(GameSceneManager* gsm) :
		Scene(gsm)
	{
		glGenVertexArrays(1, &biltVAO);
		glBindVertexArray(biltVAO);
		glGenBuffers(1, &biltVBO);
		glBindBuffer(GL_ARRAY_BUFFER, biltVBO);

		float positions[] = { -1,-1,1,-1,1,1,-1,1 };

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
		std::string checkerboardShader = "res\\FluidSimulationRes\\shaders\\checkerboardShader.frag";
		std::string displayShader = "res\\FluidSimulationRes\\shaders\\displayShaderSource.frag";
		std::string bloomPrefilterShader = "res\\FluidSimulationRes\\shaders\\bloomPrefilterShader.frag";
		std::string bloomBlurShader = "res\\FluidSimulationRes\\shaders\\bloomBlurShader.frag";
		std::string bloomFinalShader = "res\\FluidSimulationRes\\shaders\\bloomFinalShader.frag";
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
		checkerboardProgram = Shader::create(baseVertexShader, checkerboardShader);
		bloomPrefilterProgram = Shader::create(baseVertexShader, bloomPrefilterShader);
		bloomBlurProgram = Shader::create(baseVertexShader, bloomBlurShader);
		bloomFinalProgram = Shader::create(baseVertexShader, bloomFinalShader);
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

		initFramebuffers();
	}

	~FluidSimulationScene()
	{
		delete blurProgram;
		delete copyProgram;
		delete clearProgram;
		delete colorProgram;
		delete checkerboardProgram;
		delete bloomPrefilterProgram;
		delete bloomBlurProgram;
		delete bloomFinalProgram;
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

		for (int i = 0; i < pointers.size(); i++)
		{
			delete pointers[i];
		}

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

	std::unique_ptr<Scene> clone()
	{
		return std::make_unique<std::remove_reference<decltype(*this)>::type>(*this);
	}

	void handleinput() override
	{
		
	}

	void update(const float& dt) override
	{

	}

	void render(SpriteRenderer* const spriteRenderer, ShapeRenderer* const shapeRenderer) override
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(0, 0, 1, 1);
	}

private:

	void bilt(FBO* const destination)
	{
		glBindVertexArray(biltVAO);
		destination->bindFBO();
		glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
		destination->unbindFBO();
		glBindVertexArray(0);
	}

	void initFramebuffers()
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

		initSunraysFramebuffers();
	}

	void initSunraysFramebuffers()
	{
		Resolution res = getResolution(config.SUNRAYS_RESOLUTION);

		unsigned int texType = GL_HALF_FLOAT;

		PixelFormat r = { GL_R16F,GL_RED };
		
		sunrays = GL::createFBO(res.width, res.height, r.internalFormat, r.format, texType, GL_LINEAR);
		sunraysTemp = GL::createFBO(res.width, res.height, r.internalFormat, r.format, texType, GL_LINEAR);

	}

	const Config config;

	unsigned int biltVAO;

	unsigned int biltVBO;

	Shader* blurProgram; ;
	Shader* copyProgram;
	Shader* clearProgram;
	Shader* colorProgram;
	Shader* checkerboardProgram;
	Shader* bloomPrefilterProgram;
	Shader* bloomBlurProgram;
	Shader* bloomFinalProgram;
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

	std::vector<pointerPrototype*> pointers;

	DoubleFBO* dye;
	DoubleFBO* velocity;
	DoubleFBO* pressure;

	FBO* divergence;
	FBO* curl;
	FBO* sunrays;
	FBO* sunraysTemp;

};