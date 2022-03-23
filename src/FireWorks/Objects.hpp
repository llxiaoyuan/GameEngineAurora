#pragma once

#ifndef _OBJECTS_HPP_
#define _OBJECTS_HPP_

#include<Aurora/Graphics.hpp>
#include<Aurora/Math.hpp>

#include<iostream>
#include<List>

#include"ShellConfig.hpp"

class Star;

class Spark;

class Shell;

class Star
{
public:

	static constexpr float drawWidth = 1.5f;

	static constexpr float airDrag = 0.98f;

	static constexpr float airDragHeavy = 0.992f;

	static std::list<Star*>* active;

	static std::list<Star*>* pool;

	static Star* global;

	static Star* add(const float& x, const float& y, const Color& color, const float& angle, const float& speed, const float& life, const float& speedOffX = 0.f, const float& speedOffY = 0.f);

	static void returnInstance(Star* const star);

	static void free();

	bool visible;

	bool heavy;

	float x;

	float y;

	float preX;

	float preY;

	Color color;

	Color secondColor;

	bool haveSecondColor;

	bool colorChanged;

	float speedX;

	float speedY;

	float life;

	float fullLife;

	float transitionTime;

	float spinAngle;

	float spinSpeed;

	float spinRadius;

	float sparkFreq;

	float sparkSpeed;

	float sparkTimer;

	float sparkLife;

	float sparkLifeVariation;

	Color sparkColor;

	bool strobe;

	float strobeFreq;

	Shell* shell;

	void (*onDeath)();

private:

	Star() {}

};

class Spark
{
public:

	static constexpr float airDrag = 0.9f;

	static std::list<Spark*>* active;

	static std::list<Spark*>* pool;

	static Spark* add(const float& x, const float& y, const Color& color, const float& angle, const float& speed, const float& life);

	static void returnInstance(Spark* const spark);

	static void free();

	float x;

	float y;

	float preX;

	float preY;

	Color color;

	float speedX;

	float speedY;

	float life;

private:

	Spark() {}

};


class Shell
{
public:

	Star* comet;

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

	bool haveSecondColor = false;

	bool fallingLeaves = false;

	static Shell* global;

	Shell() = delete;

	Shell(const ShellConfiguration& config);

	void launch(const float& launchWidth, const float& launchHeight);

	void burst();

};


#endif // !_OBJECTS_HPP_