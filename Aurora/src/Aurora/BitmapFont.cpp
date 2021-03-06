#include<Aurora/BitmapFont.hpp>


BitmapFont::BitmapFont(const std::string& bitmapPath, const std::string& configFilePath, const int& fontSize) :
	fontSize(fontSize), originFontSize(0), scale(1)
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
		else if (temp.find("size") != std::string::npos)
		{
			Parse(temp);
			originFontSize = std::stoi(value);
			if (fontSize < 0)
			{
				this->fontSize = originFontSize;
			}
			scale = (float)this->fontSize / originFontSize;
		}
	}

	stream >> temp;

	Parse(temp);
	const int count = std::stoi(value);

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

		characterMap.insert(std::pair<char,const Character>(charID, character));

		unsigned char* buffer = new unsigned char[(long long)width * (long long)height * 4LL];

		for (int y = 0; y < height; y++)
		{
			for (int x = 0; x < width; x++)
			{
				const int pixelIndex = 4 * (y * width + x);
				const int pixelIndex2 = 4 * ((bitmapHeight - startY - height + y) * bitmapWidth + startX + x);
				buffer[pixelIndex] = bitmapBuffer[pixelIndex2];
				buffer[pixelIndex + 1] = bitmapBuffer[pixelIndex2 + 1];
				buffer[pixelIndex + 2] = bitmapBuffer[pixelIndex2 + 2];
				buffer[pixelIndex + 3] = bitmapBuffer[pixelIndex2 + 3];
			}
		}

		textures.emplace_back(new BitmapTexture(buffer, width, height, bpp));

		delete[] buffer;
	}

	stbi_image_free(bitmapBuffer);

	stream.close();

	std::cout << "[class BitmapFont] " << configFilePath << " load complete!\n";
}

BitmapFont* BitmapFont::create(const std::string& bitmapPath, const std::string& configFilePath, const int& fontSize)
{
	return new BitmapFont(bitmapPath, configFilePath, fontSize);
}

BitmapFont::~BitmapFont()
{
	std::cout << "[class BitmapFont] release!\n";
	for (int i = 0; i < textures.size(); i++)
	{
		delete textures[i];
	}
}

const  BitmapFont::Character& BitmapFont::getCharacter(const char& c)
{
	return characterMap[c];
}

const int& BitmapFont::getFontSize() const
{
	return fontSize;
}

void BitmapFont::setFontSize(const int& fontSize)
{
	this->fontSize = fontSize;
	scale = (float)fontSize / originFontSize;
}

const float& BitmapFont::getScale() const
{
	return scale;
}

void BitmapFont::draw(SpriteRenderer* const renderer, const std::string& context, const float& x, const float& y, const float& r, const float& g, const float& b, const float& a)
{
	float currentX = x;
	for (int i = 0; i < context.size(); i++)
	{
		const BitmapFont::Character& character = getCharacter(context[i]);
		renderer->bitmapTexturePoolAdd(textures[character.index]);
		const float currentY = y + character.yoffset;
		const glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.f), glm::vec3(currentX + character.xoffset, currentY, 0)), glm::vec3(getScale(), getScale(), 1));
		textures[character.index]->addColor(r, g, b, a);
		textures[character.index]->addModel(model);
		currentX += character.xadvance * getScale();
	}
}

void BitmapFont::draw(SpriteRenderer* const renderer, const char& context, const float& x, const float& y, const float& r, const float& g, const float& b, const float& a)
{
	const BitmapFont::Character& character = getCharacter(context);
	renderer->bitmapTexturePoolAdd(textures[character.index]);
	const glm::mat4 model = glm::scale(glm::translate(glm::mat4(1.f), glm::vec3(x + character.xoffset, y + character.yoffset, 0)), glm::vec3(getScale(), getScale(), 1));
	textures[character.index]->addColor(r, g, b, a);
	textures[character.index]->addModel(model);
}
