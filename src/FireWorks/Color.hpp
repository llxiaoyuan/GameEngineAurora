#pragma once

#ifndef _COLOR_HPP_
#define _COLOR_HPP_

#include<Aurora/Utility.hpp>

struct Color
{
	float r;

	float g;

	float b;

	float a;

	static Color random()
	{
		return { Utility::rFloat(),Utility::rFloat() ,Utility::rFloat(),1.f };
	}

	static const Color Gold;

	static const Color Invisible;

};

const Color Color::Gold{ 1.f,0.843f,0.f,1.f };

const Color Color::Invisible{ 0.f,0.f,0.f,0.f };

#endif // !_COLOR_HPP_