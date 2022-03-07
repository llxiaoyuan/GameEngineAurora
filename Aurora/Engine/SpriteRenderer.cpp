#include"SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer():
	texturePool()
{
	textRenderShader.create("res\\shaders\\TextRender.shader");
	instanceRenderShader.create("res\\shaders\\InstanceRender.shader");
	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);
	instanceRenderShader.bind();
	instanceRenderShader.setMatrix4fv("proj", proj);
	instanceRenderShader.unbind();
	textRenderShader.bind();
	textRenderShader.setMatrix4fv("proj", proj);
	textRenderShader.unbind();
}

SpriteRenderer::~SpriteRenderer()
{
	std::cout << "[" << typeid(*this).name() << "] release!\n";
}

void SpriteRenderer::begin()
{
	instanceRenderShader.bind();
	texturePool.clear();
}

void SpriteRenderer::end()
{
	for (size_t i = 0; i < texturePool.size(); i++)
	{
		texturePool[i]->updateMatrices();
		texturePool[i]->bind();
		glDrawArraysInstanced(GL_TRIANGLE_FAN, 0, 4, texturePool[i]->getInstanceNum());
		texturePool[i]->unbind();
		texturePool[i]->resetInstanceNum();
	}
	instanceRenderShader.unbind();
}

void SpriteRenderer::draw(Texture& texture, const float& x, const float& y, const float& originX, const float& originY, const float& rotation)
{
	texturePoolAdd(texture);
	glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0));
	model = glm::rotate(model, rotation, glm::vec3(0, 0, 1.f));
	model = glm::translate(model, glm::vec3(-originX, -originY, 0));
	texture.addModel(model);
}

void SpriteRenderer::draw(Texture& texture, const float& x, const float& y)
{
	texturePoolAdd(texture);
	glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0));
	texture.addModel(model);
}

void SpriteRenderer::texturePoolAdd(Texture& texture)
{
	bool notFind = true;
	for (int i = 0; i < texturePool.size(); i++)
	{
		if (texturePool[i] == &texture)
		{
			notFind = false;
			break;
		}
	}
	if (notFind)
	{
		texturePool.push_back(&texture);
	}
}
