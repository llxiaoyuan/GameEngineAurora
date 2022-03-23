#pragma once

#include"Color.hpp"

enum class Glitter
{
	none, light, medium, heavy, thick, streamer, willow
};

struct ShellConfiguration
{
	float shellSize = 3.f;

	float spreadSize = 0.f;

	int starCount = 0;

	float starLife = 0.f;

	float starLifeVariation = 0.f;

	float starDensity = 0.f;

	Color color;

	Color secondColor;

	Color glitterColor;

	Glitter glitter;

	Color pistilColor;

	bool streamers = false;

	bool crossette = false;

	bool floral = false;

	bool crackle = false;

	bool horseTail = false;

	bool pistil = false;

	bool ring = false;

	bool haveSecondColor = false;

	bool fallingLeaves = false;

	static float globalShellSize;

};

float ShellConfiguration::globalShellSize = 3.f;

enum class ShellType
{
	random,
	crysanthemumShell,
	ghostShell,
	strobeShell,
	palmShell,
	ringShell,
	crossetteShell,
	floralShell,
	fallingLeavesShell,
	willowShell,
	crackleShell,
	horsetailShell
};

ShellConfiguration getShellConfig(ShellType type)
{
	switch (type)
	{
	case ShellType::random:
		type = (ShellType)(rand() % 11 + 1);
	case ShellType::crysanthemumShell:
		return crysanthemumShell();
	case ShellType::ghostShell:
		break;
	case ShellType::strobeShell:
		break;
	case ShellType::palmShell:
		break;
	case ShellType::ringShell:
		break;
	case ShellType::crossetteShell:
		break;
	case ShellType::floralShell:
		break;
	case ShellType::fallingLeavesShell:
		break;
	case ShellType::willowShell:
		break;
	case ShellType::crackleShell:
		break;
	case ShellType::horsetailShell:
		break;
	default:
		break;
	}
}

ShellConfiguration crysanthemumShell()
{
	ShellConfiguration config;

	const bool glitter = Utility::rFloat() < 0.25f;

	const bool singleColor = Utility::rFloat() < 0.72f;

	if (singleColor)
	{
		config.color = Color::random();
	}
	else
	{
		config.haveSecondColor = true;
		config.color = Color::random();
		config.secondColor = Color::random();
	}

	const bool pistil = singleColor && Utility::rFloat() < 0.42f;

	config.shellSize = ShellConfiguration::globalShellSize;

	config.spreadSize = 300.f + config.shellSize * 100.f;

	config.starLife = 0.9f + config.shellSize * 0.2f;

	config.starDensity = 1.2f;

	config.glitter = glitter ? Glitter::light : Glitter::none;

	config.glitterColor = Utility::rFloat() > 0.5f ? Color{ 1,1,1,1 } : Color::Gold;

	config.pistil = pistil;

	config.pistilColor = Color::random();

	config.streamers = !pistil && Utility::rFloat() < 0.42f;

	return config;
}