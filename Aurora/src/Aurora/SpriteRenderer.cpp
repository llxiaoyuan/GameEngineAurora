#include<Aurora/SpriteRenderer.hpp>

SpriteRenderer::SpriteRenderer():
	textRenderShader(Shader::create("res\\shaders\\TextRender.shader")),
	instanceRenderShader(Shader::create("res\\shaders\\InstanceRender.shader"))
{
	const glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);
	instanceRenderShader->bind();
	instanceRenderShader->setMatrix4fv("proj", proj);
	instanceRenderShader->unbind();
	textRenderShader->bind();
	textRenderShader->setMatrix4fv("proj", proj);
	textRenderShader->unbind();
}

SpriteRenderer* SpriteRenderer::create()
{
	return new SpriteRenderer();
}

SpriteRenderer::~SpriteRenderer()
{
	std::cout << "[class SpriteRenderer] release!\n";
	if (instanceRenderShader)
	{
		delete instanceRenderShader;
	}
	if (textRenderShader)
	{
		delete textRenderShader;
	}
}

void SpriteRenderer::begin()
{
	texturePool.clear();
	bitmapTexturePool.clear();
	renderTexturePool.clear();
}

void SpriteRenderer::end()
{
	instanceRenderShader->bind();

	for (size_t i = 0; i < texturePool.size(); i++)
	{
		texturePool[i]->updateMatrices();
		texturePool[i]->bind();
		texturePool[i]->drawInstance();
		texturePool[i]->unbind();
		texturePool[i]->checkOut();
	}

	for (size_t i = 0; i < renderTexturePool.size(); i++)
	{
		renderTexturePool[i]->updateMatrices();
		glBindVertexArray(renderTexturePool[i]->VAO);
		renderTexturePool[i]->fbo->attachTexture();
		renderTexturePool[i]->drawInstance();
		renderTexturePool[i]->fbo->dettachTexture();
		glBindVertexArray(0);
		renderTexturePool[i]->checkOut();
	}

	textRenderShader->bind();

	for (size_t i = 0; i < bitmapTexturePool.size(); i++)
	{
		bitmapTexturePool[i]->update();
		bitmapTexturePool[i]->bind();
		bitmapTexturePool[i]->drawInstance();
		bitmapTexturePool[i]->unbind();
		bitmapTexturePool[i]->checkOut();
	}

	textRenderShader->unbind();
}

void SpriteRenderer::draw(Texture* const texture, const float& x, const float& y)
{
	texturePoolAdd(texture);
	glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0));
	texture->addModel(model);
}

void SpriteRenderer::draw(Texture* const texture, const float& x, const float& y, const float& originX, const float& originY)
{
	texturePoolAdd(texture);
	glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(x - originX, y - originY, 0));
	texture->addModel(model);
}

void SpriteRenderer::draw(Texture* const texture, const float& x, const float& y, const float& originX, const float& originY, const float& rotation)
{
	texturePoolAdd(texture);
	glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0));
	model = glm::rotate(model, rotation, glm::vec3(0, 0, 1.f));
	model = glm::translate(model, glm::vec3(-originX, -originY, 0));
	texture->addModel(model);
}

void SpriteRenderer::draw(RenderTexture* const renderTexture, const float& x, const float& y)
{
	renderTexturePoolAdd(renderTexture);
	glm::mat4 model = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0));
	renderTexture->addModel(model);
}

void SpriteRenderer::texturePoolAdd(Texture* const texture)
{
	if(!texture->isRegistered())
	{
		texture->checkIn();
		texturePool.emplace_back(texture);
	}
}

void SpriteRenderer::bitmapTexturePoolAdd(BitmapTexture* const texture)
{
	if (!texture->isRegistered())
	{
		texture->checkIn();
		bitmapTexturePool.emplace_back(texture);
	}
}

void SpriteRenderer::renderTexturePoolAdd(RenderTexture* const renderTexture)
{
	if (!renderTexture->isRegistered())
	{
		renderTexture->checkIn();
		renderTexturePool.emplace_back(renderTexture);
	}
}
