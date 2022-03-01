#pragma once

#include<Music.hpp>

class Score
{
public:

	Score():
		score(0),
		scoreUpTimer(.06f),
		isFlashing(false),
		flashTime(6),
		flashTimer(.3f),
		visible(true)
	{
		
	}

	~Score()
	{
		
	}


	bool isFlashing;

	int flashTime;

	Timer flashTimer;

	Timer scoreUpTimer;

	bool visible;

	int score;

	int scoreRecord;

	void update(const float& dt)
	{
		if (isFlashing)
		{
			flashTimer.update();
			if (flashTimer.reached())
			{
				visible = !visible;
				flashTimer.restart();
				flashTime--;
				if (flashTime == 0)
				{
					isFlashing = false;
					flashTime = 6;
					flashTimer.restart();
					visible = true;
				}
			}
		}


		if (score < 99999)
		{
			scoreUpTimer.update();
			if (scoreUpTimer.reached())
			{
				scoreUpTimer.restart();
				score++;
				if (score % 100 == 0)
				{
					if (!isFlashing)
					{
						Music::play("res\\DinoGameRes\\music\\reach.ogg", false);
					}
					scoreRecord = score / 100 * 100;
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
			return scoreRecord;
		}
		return score;
	}

};