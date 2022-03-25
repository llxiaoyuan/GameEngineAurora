#pragma once

#include<Aurora/Sound.hpp>

class Score
{
public:

	Score():
		score(0),
		scoreUpTimer(.06f),
		isFlashing(false),
		flashTime(6),
		flashTimer(.3f),
		visible(true),
		scoreReachSound(Sound::create("res\\DinoGameRes\\music\\reach.ogg", false))
	{
		
	}

	~Score()
	{
		delete scoreReachSound;
	}


	bool isFlashing;

	int flashTime;

	Timer flashTimer;

	Timer scoreUpTimer;

	bool visible;

	int score;

	int scoreRecord;

	Sound* scoreReachSound;

	void update(const float& dt)
	{
		if (isFlashing)
		{
			if (flashTimer.update())
			{
				visible = !visible;
				flashTime--;
				if (flashTime == 0)
				{
					isFlashing = false;
					flashTime = 6;
					visible = true;
				}
			}
		}


		if (score < 99999)
		{
			if (scoreUpTimer.update())
			{
				score++;
				if (score % 100 == 0)
				{
					if (!isFlashing)
					{
						scoreReachSound->play();
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