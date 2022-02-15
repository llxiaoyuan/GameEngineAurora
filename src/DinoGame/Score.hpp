#pragma once

#include<Music.hpp>

class Score
{
public:

	Score():
		score(0),
		scoreUpTimer(0),
		scoreUpTimeLimit(.06f),
		isFlashing(false),
		flashTime(6),
		flashTimer(0),
		flashTimerLimit(.3f),
		visible(true)
	{
		
	}

	~Score()
	{
		
	}


	bool isFlashing;

	int flashTime;

	float flashTimer;

	float flashTimerLimit;

	bool visible;

	int score;

	float scoreUpTimer;

	const float scoreUpTimeLimit;

	void update(const float& dt)
	{
		if (isFlashing)
		{
			flashTimer += dt;
			if (flashTimer > flashTimerLimit)
			{
				visible = !visible;
				flashTimer = 0;
				flashTime--;
				if (flashTime == 0)
				{
					isFlashing = false;
					flashTime = 6;
					flashTimer = 0;
					visible = true;
				}
			}
		}


		if (score < 99999)
		{
			scoreUpTimer += dt;
			if (scoreUpTimer >= scoreUpTimeLimit)
			{
				scoreUpTimer = 0;
				score++;
				if (score % 100 == 0)
				{
					if (!isFlashing)
					{
						Music::play("res\\DinoGameRes\\music\\reach.ogg", false);
					}
					isFlashing = true;
					visible = false;
				}
			}
		}
	}

	void operator=(const int& x)
	{
		score = x;
	}

	operator const int()
	{
		if (isFlashing)
		{
			return score / 100 * 100;
		}
		return score;
	}

};