#pragma once

#ifndef _GAME_HPP_
#define _GAME_HPP_

#include<iostream>
#include<memory>

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

	virtual std::shared_ptr<Game> clone() = 0;

	//¸üÐÂ
	virtual void update(const float& dt) = 0;

	//äÖÈ¾
	virtual void render() = 0;

};

#endif // !_GAME_HPP_