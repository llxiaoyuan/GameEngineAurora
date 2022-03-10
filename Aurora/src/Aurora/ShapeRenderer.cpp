#include<Aurora/ShapeRenderer.hpp>

ShapeRenderer::ShapeRenderer()
{

}

ShapeRenderer::~ShapeRenderer()
{

}

void ShapeRenderer::begin()
{
	circleRenderer.begin();
	lineRenderer.begin();
}

void ShapeRenderer::end()
{
	circleRenderer.updateCirclesData();
	lineRenderer.updateVerticesData();
	lineRenderer.end();
	circleRenderer.end();
}

void ShapeRenderer::drawLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& r, const float& g, const float& b, const float& a)
{
	lineRenderer.addLine(x1, y1, x2, y2, r, g, b, a);
}

void ShapeRenderer::drawCircle(const float& x, const float& y, const float& length, const float& r, const float& g, const float& b, const float& a)
{
	circleRenderer.addCircle(x, y, length, r, g, b, a);
}

ShapeRenderer::CircleRenderer::CircleRenderer() :
	circlePos(maxCircleNum), circleColor(maxCircleNum), circleLength(maxCircleNum), curIndex(0)
{
	circleShader.create("res\\shaders\\CircleShader.shader");
	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);

	circleShader.bind();
	circleShader.setMatrix4fv("proj", proj);
	circleShader.unbind();

	std::vector<float> positions(128);

	{
		float theta = Math::two_pi / 64;
		for (int i = 0; i < 64; i++)
		{
			positions[i * 2] = cosf(theta);
			positions[i * 2 + 1] = sinf(theta);
			theta += Math::two_pi / 64;
		}
	}

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &verticesVBO);

	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(float), positions.data(), GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	glGenBuffers(1, &circlePosVBO);
	glBindBuffer(GL_ARRAY_BUFFER, circlePosVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * maxCircleNum, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	glGenBuffers(1, &circleColorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, circleColorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * maxCircleNum, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

	glGenBuffers(1, &circleLengthVBO);
	glBindBuffer(GL_ARRAY_BUFFER, circleLengthVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maxCircleNum, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

ShapeRenderer::CircleRenderer::~CircleRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &verticesVBO);
	glDeleteBuffers(1, &circlePosVBO);
	glDeleteBuffers(1, &circleColorVBO);
	glDeleteBuffers(1, &circleLengthVBO);
}

void ShapeRenderer::CircleRenderer::begin()
{
	curIndex = 0;
}

void ShapeRenderer::CircleRenderer::end()
{
	circleShader.bind();
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_LINE_LOOP, 0, 64, curIndex);
	glBindVertexArray(0);
	circleShader.unbind();
}

void ShapeRenderer::CircleRenderer::updateCirclesData()
{
	circleShader.bind();
	glBindBuffer(GL_ARRAY_BUFFER, circlePosVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curIndex * sizeof(glm::vec2), &circlePos[0]);
	glBindBuffer(GL_ARRAY_BUFFER, circleColorVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curIndex * sizeof(glm::vec4), &circleColor[0]);
	glBindBuffer(GL_ARRAY_BUFFER, circleLengthVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curIndex * sizeof(float), &circleLength[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	circleShader.unbind();
}

void ShapeRenderer::CircleRenderer::addCircle(const float& x, const float& y, const float& length, const float& r, const float& g, const float& b, const float& a)
{
	if (length <= 1.f)//²»»­Ì«Ð¡µÄÔ²
	{
		return;
	}
	circlePos[curIndex] = glm::vec2(x, y);
	circleLength[curIndex] = length;
	circleColor[curIndex++] = glm::vec4(r, g, b, a);
}

ShapeRenderer::LineRenderer::LineRenderer() :
	vertices(maxVerticesNum * 2), colors(maxVerticesNum), curIndex(0), verticesNum(0)
{
	lineShader.create("res\\shaders\\LineShader.shader");
	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);

	lineShader.bind();
	lineShader.setMatrix4fv("proj", proj);
	lineShader.unbind();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &verticesVBO);

	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * maxVerticesNum, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ShapeRenderer::LineRenderer::~LineRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &verticesVBO);
	glDeleteBuffers(1, &colorVBO);
}

void ShapeRenderer::LineRenderer::begin()
{
	verticesNum = 0;
	curIndex = 0;
}

void ShapeRenderer::LineRenderer::end()
{
	lineShader.bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, verticesNum);
	glBindVertexArray(0);
	lineShader.unbind();
}

void ShapeRenderer::LineRenderer::updateVerticesData()
{
	lineShader.bind();
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curIndex * sizeof(float), &vertices[0]);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, verticesNum * sizeof(glm::vec4), &colors[0]);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	lineShader.unbind();
}

void ShapeRenderer::LineRenderer::addLine(const float& x1, const float& y1, const float& x2, const float& y2,const float& r,const float& g,const float& b,const float& a)
{
	vertices[curIndex++] = x1;
	vertices[curIndex++] = y1;
	vertices[curIndex++] = x2;
	vertices[curIndex++] = y2;
	colors[verticesNum++] = glm::vec4(r, g, b, a);
	colors[verticesNum++] = glm::vec4(r, g, b, a);
}
