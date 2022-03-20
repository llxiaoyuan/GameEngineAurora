#pragma once

#include"Star.hpp"
#include"Spark.hpp"

#include<Aurora/Graphics.hpp>

class Shell
{
public:

	void launch(const float& launchWidth, const float& launchHeight)
	{
		const float launchVelocity = powf(launchHeight * 0.04f, 0.64f);

		Star* const comet = Star::add(
			launchWidth,
			0,
			Color::random(),
			0,
			launchVelocity,
			launchVelocity * 0.4f
		);

		comet->heavy = true;
		comet->spinRadius = Utility::rFloat() * (0.85f - 0.32f) + 0.32f;
		comet->sparkFreq = 0.008f;
		comet->sparkLife = 0.32f;
		comet->sparkLifeVariation = 3.f;

		/*if (this.glitter == = 'willow' || this.fallingLeaves) {
			comet.sparkFreq = 20 / quality;
			comet.sparkSpeed = 0.5;
			comet.sparkLife = 500;
		}*/

		{
			int r = comet->color.r * 255;
			int g = comet->color.g * 255;
			int b = comet->color.b * 255;
			if (r == 0 && g == 0 && b == 0)
			{
				comet->sparkColor = Color::Gold;
			}
		}

		if (Utility::rFloat() > 0.4f)
		{
			std::cout << "Have second color\n";
			comet->haveSecondColor = true;
			comet->secondColor = Color::Invisible;
			comet->transitionTime = powf(Utility::rFloat(), 1.5f) * .7f + .5f;
		}


	}

};