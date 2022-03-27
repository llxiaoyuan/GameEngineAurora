#include<Aurora/ShapeRenderer.hpp>

ShapeRenderer::ShapeRenderer()
{

}

ShapeRenderer* ShapeRenderer::create()
{
	return new ShapeRenderer();
}

ShapeRenderer::~ShapeRenderer()
{
	std::cout << "[class ShapeRenderer] release!\n";
}

void ShapeRenderer::begin()
{
	circleRenderer.begin();
	rcLineRenderer.begin();
	lineRenderer.begin();
	triangleRenderer.begin();
}

void ShapeRenderer::end()
{
	if (rcLineRenderer.curVerticesNum)
	{
		rcLineRenderer.updateVerticesData();
		rcLineRenderer.end();
	}
	if (lineRenderer.curVerticesNum)
	{
		lineRenderer.updateVerticesData();
		lineRenderer.end();
	}
	if (circleRenderer.curCircleNum)
	{
		circleRenderer.updateCirclesData();
		circleRenderer.end();
	}
	if (triangleRenderer.curVerticesNum)
	{
		triangleRenderer.updateVerticesData();
		triangleRenderer.end();
	}
}

void ShapeRenderer::drawLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& r, const float& g, const float& b, const float& a)
{
	lineRenderer.addLine(x1, y1, x2, y2, r, g, b, a);
}

void ShapeRenderer::drawRCLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& width, const float& r, const float& g, const float& b, const float& a)
{
	rcLineRenderer.addLine(x1, y1, x2, y2, width, r, g, b, a);
}

void ShapeRenderer::drawFilledTriangle(const float& x1, const float& y1, const float& x2, const float& y2, const float& x3, const float& y3, const float& r, const float& g, const float& b, const float& a)
{
	triangleRenderer.addVertex(x1, y1, r, g, b, a);
	triangleRenderer.addVertex(x2, y2, r, g, b, a);
	triangleRenderer.addVertex(x3, y3, r, g, b, a);
}

void ShapeRenderer::drawRect(const Rect& rect, const float& r, const float& g, const float& b, const float& a)
{
	lineRenderer.addLine(rect.getX(), rect.getY(), rect.getX() + rect.getWidth(), rect.getY(), r, g, b, a);
	lineRenderer.addLine(rect.getX() + rect.getWidth(), rect.getY(), rect.getX() + rect.getWidth(), rect.getY() + rect.getHeight(), r, g, b, a);
	lineRenderer.addLine(rect.getX(), rect.getY() + rect.getHeight(), rect.getX() + rect.getWidth(), rect.getY() + rect.getHeight(), r, g, b, a);
	lineRenderer.addLine(rect.getX(), rect.getY(), rect.getX(), rect.getY() + rect.getHeight(), r, g, b, a);
}

void ShapeRenderer::drawRect(const float& x, const float& y, const float& width, const float& height, const float& r, const float& g, const float& b, const float& a)
{
	lineRenderer.addLine(x, y, x + width, y, r, g, b, a);
	lineRenderer.addLine(x + width, y, x + width, y + height, r, g, b, a);
	lineRenderer.addLine(x, y + height, x + width, y + height, r, g, b, a);
	lineRenderer.addLine(x, y, x, y + height, r, g, b, a);
}

void ShapeRenderer::drawFilledRect(const float& x, const float& y, const float& width, const float& height, const float& r, const float& g, const float& b, const float& a)
{
	triangleRenderer.addVertex(x, y, r, g, b, a);
	triangleRenderer.addVertex(x + width, y, r, g, b, a);
	triangleRenderer.addVertex(x + width, y + height, r, g, b, a);
	triangleRenderer.addVertex(x, y, r, g, b, a);
	triangleRenderer.addVertex(x + width, y + height, r, g, b, a);
	triangleRenderer.addVertex(x, y + height, r, g, b, a);
}

void ShapeRenderer::drawCircle(const float& x, const float& y, const float& length, const float& r, const float& g, const float& b, const float& a)
{
	circleRenderer.addCircle(x, y, length, r, g, b, a);
}

ShapeRenderer::CircleRenderer::CircleRenderer() :
	curCircleNum(0), circlePos(new glm::vec2[maxCircleNum]), circleColor(new glm::vec4[maxCircleNum]), circleLength(new float[maxCircleNum]),
	circleShader(Shader::create("res\\shaders\\circleShader.shader"))
{
	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);

	circleShader->bind();
	circleShader->setMatrix4fv("proj", proj);
	circleShader->unbind();

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
	if (circlePos)
	{
		delete[] circlePos;
	}
	if (circleColor)
	{
		delete[] circleColor;
	}
	if (circleLength)
	{
		delete[] circleLength;
	}
	if (circleShader)
	{
		delete circleShader;
	}
}

void ShapeRenderer::CircleRenderer::begin()
{
	curCircleNum = 0;
}

void ShapeRenderer::CircleRenderer::end()
{
	circleShader->bind();
	glBindVertexArray(VAO);
	glDrawArraysInstanced(GL_LINE_LOOP, 0, 64, curCircleNum);
	glBindVertexArray(0);
	circleShader->unbind();
}

void ShapeRenderer::CircleRenderer::updateCirclesData()
{
	glBindBuffer(GL_ARRAY_BUFFER, circlePosVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curCircleNum * sizeof(glm::vec2), circlePos);
	glBindBuffer(GL_ARRAY_BUFFER, circleColorVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curCircleNum * sizeof(glm::vec4), circleColor);
	glBindBuffer(GL_ARRAY_BUFFER, circleLengthVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curCircleNum * sizeof(float), circleLength);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ShapeRenderer::CircleRenderer::addCircle(const float& x, const float& y, const float& length, const float& r, const float& g, const float& b, const float& a)
{
	if (length <= 1.f)//²»»­Ì«Ð¡µÄÔ²
	{
		return;
	}
	circlePos[curCircleNum] = glm::vec2(x, y);
	circleLength[curCircleNum] = length;
	circleColor[curCircleNum++] = glm::vec4(r, g, b, a);
}

ShapeRenderer::LineRenderer::LineRenderer() :
	curVerticesNum(0), vertices(new glm::vec2[maxVerticesNum]), colors(new glm::vec4[maxVerticesNum]),
	lineShader(Shader::create("res\\shaders\\ShapeShader.shader"))
{
	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);

	lineShader->bind();
	lineShader->setMatrix4fv("proj", proj);
	lineShader->unbind();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &verticesVBO);

	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * maxVerticesNum, nullptr, GL_DYNAMIC_DRAW);
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
	if (vertices)
	{
		delete[] vertices;
	}
	if (colors)
	{
		delete[] colors;
	}
	if (lineShader)
	{
		delete lineShader;
	}
}

void ShapeRenderer::LineRenderer::begin()
{
	curVerticesNum = 0;
}

void ShapeRenderer::LineRenderer::end()
{
	lineShader->bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, curVerticesNum);
	glBindVertexArray(0);
	lineShader->unbind();
}

void ShapeRenderer::LineRenderer::updateVerticesData()
{
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curVerticesNum * sizeof(glm::vec2), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curVerticesNum * sizeof(glm::vec4), colors);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ShapeRenderer::LineRenderer::addLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& r, const float& g, const float& b, const float& a)
{
	vertices[curVerticesNum] = glm::vec2(x1, y1);
	colors[curVerticesNum++] = glm::vec4(r, g, b, a);
	vertices[curVerticesNum] = glm::vec2(x2, y2);
	colors[curVerticesNum++] = glm::vec4(r, g, b, a);
}

ShapeRenderer::TriangleRenderer::TriangleRenderer() :
	curVerticesNum(0), vertices(new glm::vec2[maxVerticesNum]), colors(new glm::vec4[maxVerticesNum]),
	triangleShader(Shader::create("res\\shaders\\ShapeShader.shader"))
{
	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);

	triangleShader->bind();
	triangleShader->setMatrix4fv("proj", proj);
	triangleShader->unbind();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &verticesVBO);

	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * maxVerticesNum, nullptr, GL_DYNAMIC_DRAW);
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

ShapeRenderer::TriangleRenderer::~TriangleRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &verticesVBO);
	glDeleteBuffers(1, &colorVBO);
	if (vertices)
	{
		delete[] vertices;
	}
	if (colors)
	{
		delete[] colors;
	}
	if (triangleShader)
	{
		delete triangleShader;
	}
}

void ShapeRenderer::TriangleRenderer::begin()
{
	curVerticesNum = 0;
}

void ShapeRenderer::TriangleRenderer::end()
{
	triangleShader->bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, curVerticesNum);
	glBindVertexArray(0);
	triangleShader->unbind();
}

void ShapeRenderer::TriangleRenderer::updateVerticesData()
{
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curVerticesNum * sizeof(glm::vec2), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curVerticesNum * sizeof(glm::vec4), colors);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ShapeRenderer::TriangleRenderer::addVertex(const float& x1, const float& y1, const float& r, const float& g, const float& b, const float& a)
{
	vertices[curVerticesNum] = glm::vec2(x1, y1);
	colors[curVerticesNum++] = glm::vec4(r, g, b, a);
}

ShapeRenderer::RCLineRenderer::RCLineRenderer() :
	curVerticesNum(0), vertices(new glm::vec2[maxVerticesNum]), colors(new glm::vec4[maxVerticesNum]), widthArray(new float[maxVerticesNum]),
	rcLineShader(Shader::create("res\\shaders\\RCLineRender.shader"))
{
	glm::mat4 proj = glm::ortho(0.f, (float)Graphics::getWidth(), 0.f, (float)Graphics::getHeight(), -1.f, 1.f);

	rcLineShader->bind();
	rcLineShader->setMatrix4fv("proj", proj);
	rcLineShader->unbind();

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &verticesVBO);

	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * maxVerticesNum, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(glm::vec2), (void*)0);

	glGenBuffers(1, &colorVBO);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * maxVerticesNum, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(glm::vec4), (void*)0);

	glGenBuffers(1, &widthVBO);
	glBindBuffer(GL_ARRAY_BUFFER, widthVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * maxVerticesNum, nullptr, GL_DYNAMIC_DRAW);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(float), (void*)0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

ShapeRenderer::RCLineRenderer::~RCLineRenderer()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &verticesVBO);
	glDeleteBuffers(1, &colorVBO);
	glDeleteBuffers(1, &widthVBO);
	if (vertices)
	{
		delete[] vertices;
	}
	if (colors)
	{
		delete[] colors;
	}
	if (widthArray)
	{
		delete[] widthArray;
	}
	if (rcLineShader)
	{
		delete rcLineShader;
	}
}

void ShapeRenderer::RCLineRenderer::begin()
{
	curVerticesNum = 0;
}

void ShapeRenderer::RCLineRenderer::end()
{
	rcLineShader->bind();
	glBindVertexArray(VAO);
	glDrawArrays(GL_LINES, 0, curVerticesNum);
	glBindVertexArray(0);
	rcLineShader->unbind();
}

void ShapeRenderer::RCLineRenderer::updateVerticesData()
{
	glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curVerticesNum * sizeof(glm::vec2), vertices);
	glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curVerticesNum * sizeof(glm::vec4), colors);
	glBindBuffer(GL_ARRAY_BUFFER, widthVBO);
	glBufferSubData(GL_ARRAY_BUFFER, 0, curVerticesNum * sizeof(float), widthArray);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void ShapeRenderer::RCLineRenderer::addLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& width, const float& r, const float& g, const float& b, const float& a)
{
	vertices[curVerticesNum] = glm::vec2(x1, y1);
	widthArray[curVerticesNum] = width;
	colors[curVerticesNum++] = glm::vec4(r, g, b, a);
	vertices[curVerticesNum] = glm::vec2(x2, y2);
	widthArray[curVerticesNum] = width;
	colors[curVerticesNum++] = glm::vec4(r, g, b, a);
}
