#pragma once

#ifndef _SHAPE_RENDERER_HPP_
#define _SHAPE_RENDERER_HPP_

#include<glm/gtc/matrix_transform.hpp>

#include"Math.hpp"
#include"Graphics.hpp"
#include"Shader.hpp"
#include"Rect.hpp"

class ShapeRenderer
{
public:

	static ShapeRenderer* create();

	ShapeRenderer(const ShapeRenderer&) = delete;

	~ShapeRenderer();

	void begin();

	void end();

	void drawLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& r, const float& g, const float& b, const float& a = 1.f);

	void drawRCLine(const float& x1, const float& y1, const float& x2, const float& y2, const float& width, const float& r, const float& g, const float& b, const float& a = 1.f);

	void drawFilledTriangle(const float& x1, const float& y1, const float& x2, const float& y2, const float& x3, const float& y3, const float& r, const float& g, const float& b, const float& a = 1.f);

	void drawRect(const Rect& rect, const float& r, const float& g, const float& b, const float& a = 1.f);

	void drawRect(const float& x, const float& y, const float& width, const float& height, const float& r, const float& g, const float& b, const float& a = 1.f);

	void drawFilledRect(const float& x, const float& y, const float& width, const float& height, const float& r, const float& g, const float& b, const float& a = 1.f);

	void drawCircle(const float& x, const float& y, const float& length, const float& r, const float& g, const float& b, const float& a = 1.f);

private:

	ShapeRenderer();

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

		static constexpr int maxCircleNum = 100000;

		glm::vec2* circlePos;

		glm::vec4* circleColor;

		float* circleLength;

		int curCircleNum;

		Shader* circleShader;

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

		static constexpr int maxVerticesNum = 500000;

		glm::vec2* vertices;

		glm::vec4* colors;

		int curVerticesNum;

		Shader* lineShader;

	} lineRenderer;

	class RCLineRenderer
	{
	public:

		RCLineRenderer();

		~RCLineRenderer();

		void begin();

		void end();

		void updateVerticesData();

		void addLine(const float& x1, const float& y1, const float& x2, const float& y2,const float& wdith, const float& r, const float& g, const float& b, const float& a);

		unsigned int VAO;

		unsigned int verticesVBO;

		unsigned int colorVBO;

		unsigned int widthVBO;

		static constexpr int maxVerticesNum = 500000;

		glm::vec2* vertices;

		glm::vec4* colors;

		float* widthArray;

		int curVerticesNum;

		Shader* rcLineShader;
	} rcLineRenderer;

	class TriangleRenderer
	{
	public:

		TriangleRenderer();

		~TriangleRenderer();

		void begin();

		void end();

		void updateVerticesData();

		void addVertex(const float& x1, const float& y1, const float& r, const float& g, const float& b, const float& a);

		unsigned int VAO;

		unsigned int verticesVBO;

		unsigned int colorVBO;

		static constexpr int maxVerticesNum = 500000;

		glm::vec2* vertices;

		glm::vec4* colors;

		int curVerticesNum;

		Shader* triangleShader;

	} triangleRenderer;
};


#endif // !_SHAPE_RENDERER_HPP_
