#pragma once

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include<iostream>

class Game
{
public:

	Game()
	{

	}

	virtual ~Game() 
	{
		std::cout << "[class Game] release!\n";
	}

	virtual void update(const float& dt) = 0;

	virtual void render() = 0;

};

#endif // !_GAME_HPP_