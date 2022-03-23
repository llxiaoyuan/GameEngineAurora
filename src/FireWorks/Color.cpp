#include"Color.hpp"

Color Color::random()
{
	return { Utility::rFloat(),Utility::rFloat() ,Utility::rFloat(),1.f };
}

bool Color::operator==(const Color& c)
{
	return (r == c.r && g == c.g && b == c.b);
}

const Color Color::Gold{ 1.f,0.843f,0.f,1.f };

const Color Color::White{ 1.f,1.f,1.f,1.f };

const Color Color::Invisible{ 0.f,0.f,0.f,0.f };