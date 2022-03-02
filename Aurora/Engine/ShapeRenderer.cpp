#include"ShapeRenderer.hpp"

ShapeRenderer::ShapeRenderer() :
	positions(256,0)
{
	defaultShader.create("res\\shaders\\ShapeBasic.shader");

	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);
	defaultShader.bind();
	defaultShader.setMatrix4fv("proj", proj);
	defaultShader.unbind();

	glGenVertexArrays(1, &polygonVAO);
	glBindVertexArray(polygonVAO);
	glGenBuffers(1, &polygonVBO);
	glBindBuffer(GL_ARRAY_BUFFER, polygonVBO);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), nullptr, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(0 * sizeof(float)));
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ShapeRenderer::~ShapeRenderer()
{
	glDeleteBuffers(1, &polygonVBO);
	glDeleteVertexArrays(1, &polygonVAO);
}

void ShapeRenderer::begin()
{
	defaultShader.bind();
}

void ShapeRenderer::end()
{
	glUseProgram(0);
}

void ShapeRenderer::drawLine(const glm::vec2& start, const glm::vec2& end)
{
	positions[0] = start.x;
	positions[1] = start.y;
	positions[2] = end.x;
	positions[3] = end.y;

	glBindBuffer(GL_ARRAY_BUFFER, polygonVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 4, positions.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(polygonVAO);
	glDrawArrays(GL_LINES, 0, 2);
	glBindVertexArray(0);
}

void ShapeRenderer::drawRCLine(const glm::vec2& start, const glm::vec2& end, const float& width, const float& r, const float& g, const float& b, const float& a)
{
	const glm::vec2 dir = end - start;

	positions[0] = start.x;
	positions[1] = start.y;

	float ang = atan2f(dir.x, -dir.y);

	for (int i = 0; i < 9; i++)
	{
		positions[(1 + i) * 2] = start.x + width / 2.f * cosf(ang);
		positions[(1 + i) * 2 + 1] = start.y + width / 2.f * sinf(ang);
		ang += Math::pi / 8.f;
	}

	ang -= Math::pi / 8.f;

	for (int i = 10; i < 19; i++)
	{
		positions[i * 2] = end.x + width / 2.f * cosf(ang);
		positions[i * 2 + 1] = end.y + width / 2.f * sinf(ang);
		ang += Math::pi / 8.f;
	}

	positions[38] = positions[2];
	positions[39] = positions[3];

	defaultShader.setVec4f("u_color", r, g, b, a);

	glBindBuffer(GL_ARRAY_BUFFER, polygonVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 40, positions.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(polygonVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 20);
	glBindVertexArray(0);

}

void ShapeRenderer::drawRect(const glm::vec2& pos, const glm::vec2 rect, const float& r, const float& g, const float& b, const float& a)
{
	positions[0] = pos.x;
	positions[1] = pos.y;

	positions[2] = pos.x + rect.x;
	positions[3] = pos.y;

	positions[4] = pos.x + rect.x;
	positions[5] = pos.y + rect.y;

	positions[6] = pos.x;
	positions[7] = pos.y + rect.y;

	defaultShader.setVec4f("u_color", r, g, b, a);

	glBindBuffer(GL_ARRAY_BUFFER, polygonVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * 8, positions.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(polygonVAO);
	glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
	glBindVertexArray(0);
}
