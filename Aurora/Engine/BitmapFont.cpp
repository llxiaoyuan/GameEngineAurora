#include"BitmapFont.hpp"


BitmapFont::BitmapFont(const std::string& bitmapPath, const std::string& configFilePath)
{
	std::ifstream stream(configFilePath);

	std::string temp;
	std::string attr;
	std::string value;

	auto Parse = [&](const std::string& str)->void
	{
		for (int i = 0; i < str.size(); i++)
		{
			if (str[i] == '=')
			{
				attr = str.substr(0, i);
				value = str.substr(i + 1, str.size() - i - 1);
				break;
			}
		}
	};

	while (1)
	{
		stream >> temp;
		if (temp == "chars")
		{
			break;
		}
		else if (temp.find("size")!=std::string::npos)
		{
			Parse(temp);
			fontSize = std::stoi(value);;
		}
	}

	stream >> temp;

	Parse(temp);
	int count = std::stoi(value);

	unsigned char* bitmapBuffer;

	int bitmapWidth, bitmapHeight, bpp;

	stbi_set_flip_vertically_on_load(1);

	bitmapBuffer = stbi_load(bitmapPath.c_str(), &bitmapWidth, &bitmapHeight, &bpp, 4);

	for (int i = 0; i < count; i++)
	{
		int charID, startX, startY, width, height, xoffset, yoffset, xadvance;

		stream >> temp;

		for (int attrIndex = 0; attrIndex < 10; attrIndex++)
		{
			stream >> temp;

			Parse(temp);

			if (attr == "id")
			{
				charID = std::stoi(value);
			}
			else if (attr == "x")
			{
				startX = std::stoi(value);
			}
			else if (attr == "y")
			{
				startY = std::stoi(value);
			}
			else if (attr == "width")
			{
				width = std::stoi(value);
			}
			else if (attr == "height")
			{
				height = std::stoi(value);
			}
			else if (attr == "xoffset")
			{
				xoffset = std::stoi(value);
			}
			else if (attr == "yoffset")
			{
				yoffset = std::stoi(value);
			}
			else if (attr == "xadvance")
			{
				xadvance = std::stoi(value);
			}
		}

		Character character{ i,xoffset,-yoffset - height,xadvance };

		keyMap.insert(std::pair<char, Character>(charID, character));

		unsigned char* buffer = new unsigned char[(long long)width * (long long)height * 4LL];

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				int pixelIndex = 4 * (y * width + x);
				int pixelIndex2 = 4 * ((bitmapHeight - startY - height + y) * bitmapWidth + startX + x);
				buffer[pixelIndex] = bitmapBuffer[pixelIndex2];
				buffer[pixelIndex + 1] = bitmapBuffer[pixelIndex2 + 1];
				buffer[pixelIndex + 2] = bitmapBuffer[pixelIndex2 + 2];
				buffer[pixelIndex + 3] = bitmapBuffer[pixelIndex2 + 3];
			}
		}

		texturebuffers.push_back(Texture(buffer, width, height, bpp, 0, 0));

		delete[] buffer;
	}

	stbi_image_free(bitmapBuffer);

	stream.close();

	std::cout << "[BitmapFont] font load complete!\n";
}

BitmapFont::~BitmapFont()
{
	for (int i = 0; i < texturebuffers.size(); i++)
	{
		texturebuffers[i].dispose();
	}
}

Texture& BitmapFont::getTexture(const int& index)
{
	return texturebuffers[index];
}

const  BitmapFont::Character& BitmapFont::getCharacter(const char& c)
{
	return keyMap[c];
}

const int& BitmapFont::getFontSize()
{
	return fontSize;
}

