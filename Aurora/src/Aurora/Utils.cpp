#include<Aurora/Utils.hpp>

std::string Utils::File::readAllText(const std::string& filePath)
{
	std::ifstream stream(filePath);
	std::string str;
	if (stream)
	{
		std::ostringstream ss;
		ss << stream.rdbuf();
		str = ss.str();
	}
	return str;
}
