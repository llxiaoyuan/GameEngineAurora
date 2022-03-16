#pragma once

#ifndef _UTILITY_HPP_
#define _UTILITY_HPP_


#include<cstdlib>

class Utility
{
public:

	Utility() = delete;

	Utility(const Utility&) = delete;

	//产生一个[0,1]的浮点数
	static float rFloat();

};


#endif // !_UTILITY_HPP_