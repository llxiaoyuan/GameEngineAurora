#pragma once

#ifndef _SHAPE_RENDERER_HPP_
#define _SHAPE_RENDERER_HPP_

#include<glm/gtc/matrix_transform.hpp>

#include"Math.hpp"
#include"Graphics.hpp"
#include"Shader.hpp"

//图形渲染
class ShapeRenderer
{
public:

	ShapeRenderer();

	~ShapeRenderer();

	void begin();

	void end();

	void drawLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& r, const float& g, const float& b, const float& a = 1.f);

	void drawCircle(const float& x, const float& y, const float& length, const float& r, const float& g, const float& b, const float& a = 1.f);

private:

	//同一时间最多画50000个圆和SpriteRenderer绘制方法类似
	class CircleRenderer
	{
	public:

		CircleRenderer();

		~CircleRenderer();

		void begin();

		void end();

		void updateCirclesData();

		void addCircle(const float& x, const float& y, const float& length, const float& r, const float& g, const float& b, const float& a);

		unsigned int VAO;

		unsigned int verticesVBO;

		unsigned int circlePosVBO;

		unsigned int circleColorVBO;

		unsigned int circleLengthVBO;

		std::vector<glm::vec2> circlePos;

		std::vector<glm::vec4> circleColor;

		std::vector<float> circleLength;
		
		int curIndex;

		Shader circleShader;

		static constexpr int maxCircleNum = 100000;

	} circleRenderer;

	class LineRenderer
	{
	public:

		LineRenderer();

		~LineRenderer();

		void begin();

		void end();

		void updateVerticesData();

		void addLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& r, const float& g, const float& b, const float& a);

		unsigned int VAO;

		unsigned int verticesVBO;

		unsigned int colorVBO;

		std::vector<float> vertices;

		std::vector<glm::vec4> colors;

		int curIndex;

		int verticesNum;

		Shader lineShader;

		static constexpr int maxVerticesNum = 1000000;

	} lineRenderer;

};


#endif // !_SHAPE_RENDERER_HPP_
