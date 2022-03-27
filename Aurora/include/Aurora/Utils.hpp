#pragma once

#ifndef _UTILS_HPP_
#define _UTILS_HPP_


#include<cstdlib>
#include<string>
#include<fstream>
#include<sstream>

class Utils
{
public:

	Utils() = delete;

	Utils(const Utils&) = delete;

	class File
	{
	public:

		File() = delete;

		File(const File&) = delete;

		static std::string readAllText(const std::string& filePath);

	};

};


#endif // !_UTILITY_HPP_