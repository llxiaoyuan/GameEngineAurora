#include"SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer()
{
	defaultShader.create("res\\shaders\\Basic.shader");
	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);
	defaultShader.bind();
	defaultShader.setMatrix4fv("proj", proj);
	defaultShader.unbind();
}

SpriteRenderer::~SpriteRenderer()
{
	std::cout << "[" << typeid(*this).name() << "] release!\n";
}

void SpriteRenderer::begin()
{
	defaultShader.bind();
	drawTexture.clear();
}

void SpriteRenderer::end()
{
	glUseProgram(0);
}

void SpriteRenderer::draw(Actor& actor)
{
	defaultShader.setVec4f("spriteColor", 1, 1, 1, 1);
	glm::mat4 pos = glm::translate(glm::mat4(1.f), actor.getPosition());
	defaultShader.setMatrix4fv("pos", pos);
	actor.render();
}

void SpriteRenderer::draw(BitmapFont& bitmapFont, const std::string& context, const float& x, const float& y,const float& r,const float& g,const float& b,const float& a) const
{
	defaultShader.setVec4f("spriteColor", r, g, b, a);
	float currentX = x;
	for (int i = 0; i < context.size(); i++)
	{
		const BitmapFont::Character& character = bitmapFont.getCharacter(context[i]);
		const float currentY = y +  character.yoffset;
		glm::mat4 pos = glm::translate(glm::mat4(1.f), glm::vec3(currentX + character.xoffset, currentY, 0));
		pos = glm::scale(pos, glm::vec3(bitmapFont.getScale(), bitmapFont.getScale(), 1));
		defaultShader.setMatrix4fv("pos", pos);
		bitmapFont.getTexture(character.index).draw();
		currentX += character.xadvance * bitmapFont.getScale();
	}
}

void SpriteRenderer::draw(BitmapFont& bitmapFont, const char& c, const float& x, const float& y, const float& r, const float& g, const float& b, const float& a) const
{
	defaultShader.setVec4f("spriteColor", r, g, b, a);
	const BitmapFont::Character& character = bitmapFont.getCharacter(c);
	glm::mat4 pos = glm::translate(glm::mat4(1.f), glm::vec3(x + character.xoffset, y + character.yoffset, 0));
	pos = glm::scale(pos, glm::vec3(bitmapFont.getScale(), bitmapFont.getScale(), 1));
	defaultShader.setMatrix4fv("pos", pos);
	bitmapFont.getTexture(character.index).draw();
}

void SpriteRenderer::draw(Texture& texture, const float& x, const float& y, const float& originX, const float& originY, const float& rotation) const
{
	defaultShader.setVec4f("spriteColor", 1, 1, 1, 1);
	glm::mat4 pos = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0));
	pos = glm::rotate(pos, rotation * Math::degToRad, glm::vec3(0, 0, 1.f));
	pos = glm::translate(pos, glm::vec3(-originX, -originY, 0));
	defaultShader.setMatrix4fv("pos", pos);
	texture.draw();
}

void SpriteRenderer::draw(Texture& texture, const float& x, const float& y) const
{
	defaultShader.setVec4f("spriteColor", 1, 1, 1, 1);
	glm::mat4 pos = glm::translate(glm::mat4(1.f), glm::vec3(x, y, 0));
	defaultShader.setMatrix4fv("pos", pos);
	texture.draw();
}
