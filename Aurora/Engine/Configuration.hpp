#pragma once

#ifndef _CONFIGURATION_HPP_
#define _CONFIGURATION_HPP_

#include<string>

class Configuration
{
public:

	Configuration(const int& screenWidth, const int& screenHeight, const std::string& title);

	const int screenWidth;

	const int screenHeight;

	const std::string title;

};

#endif // !_CONFIGURATION_HPP_
