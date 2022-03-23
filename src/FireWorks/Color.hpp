#pragma once

#include<Aurora/Utility.hpp>

#ifndef _COLOR_HPP_
#define _COLOR_HPP_

struct Color
{
	float r;

	float g;

	float b;

	float a;

	static Color random();

	static const Color Gold;

	static const Color White;

	static const Color Invisible;

	bool operator==(const Color&);

};

#endif // !_COLOR_HPP_