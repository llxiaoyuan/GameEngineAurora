#pragma once

#ifndef _MATH_HPP_
#define _MATH_HPP_

#include<cmath>

//��ѧ�� ������һЩ���õĳ���
class Math
{
public:

	Math() = delete;

	Math(const Math&) = delete;

	static constexpr float pi = 3.1415926535897932384626433832795f;

	static constexpr float half_pi = 1.5707963267948966192313216916398f;

	static constexpr float two_pi = 6.283185307179586476925286766559f;

	static constexpr float radToDeg = 57.295779513082320876798154814105f;

	static constexpr float degToRad = 0.01745329251994329576923690768489f;

	static float lerp(const float& start, const float& end, const float& t);

};


#endif // !_MATH_HPP_
