#pragma once

#ifndef _SHAPE_RENDERER_HPP_
#define _SHAPE_RENDERER_HPP_

#include<glm/gtc/matrix_transform.hpp>

#include"Math.hpp"
#include"Graphics.hpp"
#include"Shader.hpp"


class ShapeRenderer
{
public:

	ShapeRenderer();

	~ShapeRenderer();

	void begin();

	void end();

	void drawLine(const glm::vec2& start, const glm::vec2& end);

	void drawRCLine(const glm::vec2& start, const glm::vec2& end, const float& width, float r, float g, float b, float a);

	void drawRect(const glm::vec2& pos, const glm::vec2 rect, float r, float g, float b, float a);

private:

	std::vector<float> positions;

	unsigned int VAO;

	unsigned int VBO;

	Shader defaultShader;

};


#endif // !_SHAPE_RENDERER_HPP_
