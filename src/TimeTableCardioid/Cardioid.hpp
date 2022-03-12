#pragma once

#include<vector>
#include<glm/glm.hpp>

constexpr double Pi = 3.1415926535897932384626433832795;

class Cardioid
{
public:

	const double radius;

	const double offset;

	glm::vec2 center;

	std::vector<glm::vec2> points;

	const size_t pointsNum;

	Cardioid(double _radius, glm::vec2 _center, size_t _pointsNum, double _offset) :offset(_offset), radius(_radius), pointsNum(_pointsNum)
	{
		center = _center;
	}

	void cal()
	{
		points = std::vector<glm::vec2>(pointsNum);

		double rads;
		double x;
		double y;

		for (size_t i = 0; i < pointsNum; i++)
		{
			rads = 2.L * i / (double)pointsNum * Pi + offset;
			x = center.x + radius * cos(rads);
			y = center.y + radius * sin(rads);
			points[i] = glm::vec2(x, y);
		}

	}

};