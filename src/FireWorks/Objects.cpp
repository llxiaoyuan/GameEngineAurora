#include"Objects.hpp"

Star* Star::global;

Shell* Shell::global;

std::list<Star*>* Star::active = nullptr;

std::list<Star*>* Star::pool = nullptr;

std::list<Spark*>* Spark::active = nullptr;

std::list<Spark*>* Spark::pool = nullptr;

float global_sparkFreq;
float global_sparkSpeed;
float global_sparkLife;
float global_sparkLifeVariation;

void createParticleArc(const float& start, const float& arcLength, const int& count, const float& randomness, void (*particleFactory)(const float&))
{
	const float angleDelta = arcLength / count;

	const float end = start + arcLength - (angleDelta * 0.5f);

	if (end > start)
	{
		for (float angle = start; angle < end; angle += angleDelta)
		{
			particleFactory(angle + Utility::rFloat() * angleDelta * randomness);
		}
	}
	else
	{
		for (float angle = start; angle > end; angle += angleDelta)
		{
			particleFactory(angle + Utility::rFloat() * angleDelta * randomness);
		}
	}
}

void createBurst(const int& count, void (*particleFactory)(const float&, const float&), const float& startAngle = 0, const float arcLength = Math::two_pi)
{
	const float R = 0.5f * sqrtf(count / Math::pi);

	const float C = 2.f * R * Math::pi;

	const float C_HALF = C / 2.f;

	for (int i = 0; i <= C_HALF; i++)
	{
		const float ringAngle = i / C_HALF * Math::half_pi;
		const float ringSize = cosf(ringAngle);
		const float partsPerFullRing = C * ringSize;
		const float partsPerArc = partsPerFullRing * (arcLength / Math::two_pi);

		const float angleInc = Math::two_pi / partsPerFullRing;
		const float angleOffset = Utility::rFloat() * angleInc + startAngle;
		const float maxRandomAngleOffset = angleInc * 0.33f;

		for (int j = 0; j < partsPerArc; j++)
		{
			const float randomAngleOffset = Utility::rFloat() * maxRandomAngleOffset;
			const float angle = angleInc * j + angleOffset + randomAngleOffset;
			particleFactory(angle, ringSize);
		}
	}
}

void crossetteEffect()
{
	const float startAngle = Utility::rFloat() * Math::half_pi;
	auto particleFactory = [](const float& angle)
	{
		Star::add(
			Star::global->x,
			Star::global->y,
			Star::global->color,
			angle,
			Utility::rFloat() * 0.6f + 0.75f,
			0.6f
		);
	};
	createParticleArc(startAngle, Math::two_pi, 4, 0.5f, particleFactory);
}

void floralEffect()
{
	const int count = 30;
	auto particleFactory = [](const float& angle, const float& speedMult)
	{
		Star* const star = Star::add(
			Star::global->x,
			Star::global->y,
			Star::global->color,
			angle,
			speedMult * 2.4f,
			1.f + Utility::rFloat() * .3f,
			Star::global->speedX,
			Star::global->speedY
		);
	};
	createBurst(count, particleFactory);
}

void fallingLeavesEffect()
{
	auto particleFactory = [](const float& angle, const float& speedMult)
	{
		Star* const star = Star::add(
			Star::global->x,
			Star::global->y,
			Color::Invisible,
			angle,
			speedMult * 2.4f,
			2.4f + Utility::rFloat() * 0.6f,
			Star::global->speedX,
			Star::global->speedY
		);
		star->sparkColor = Color::Gold;
		star->sparkFreq = 0.048f;
		star->sparkSpeed = 0.28f;
		star->sparkLife = 0.75f;
		star->sparkLifeVariation = 3.2f;
	};
	createBurst(7, particleFactory);
}

void crackleEffect()
{
	const int count = 32;
	auto particleFactory = [](const float& angle)
	{
		Spark::add(
			Star::global->x,
			Star::global->y,
			Color::Gold,
			angle,
			powf(Utility::rFloat(), 0.45f) * 2.4f,
			0.3f + Utility::rFloat() * 0.2f
		);
	};
	createParticleArc(0, Math::two_pi, count, 1.8f, particleFactory);
}

Star* Star::add(const float& x, const float& y, const Color& color, const float& angle, const float& speed, const float& life, const float& speedOffX, const float& speedOffY)
{
	Star* instance = nullptr;

	if (!pool->empty())
	{
		instance = pool->back();
		pool->pop_back();
	}
	else
	{
		instance = new Star();
	}

	instance->visible = true;
	instance->heavy = false;
	instance->x = x;
	instance->y = y;
	instance->preX = x;
	instance->preY = y;
	instance->color = color;
	instance->speedX = sinf(angle) * speed + speedOffX;
	instance->speedY = cosf(angle) * speed + speedOffY;
	instance->life = life;
	instance->fullLife = life;
	instance->spinAngle = Utility::rFloat() * Math::two_pi;
	instance->spinSpeed = 0.8f;
	instance->spinRadius = 0;
	instance->sparkFreq = 0;
	instance->sparkSpeed = 1;
	instance->sparkTimer = 0;
	instance->sparkColor = color;
	instance->sparkLife = 0.75f;
	instance->sparkLifeVariation = 0.25f;
	instance->strobe = false;
	instance->haveSecondColor = false;
	instance->transitionTime = 0;
	instance->colorChanged = false;
	instance->strobeFreq = 0;

	instance->onDeath = nullptr;
	instance->shell = nullptr;

	active->push_back(instance);
	return instance;
}

void Star::returnInstance(Star* const star)
{
	global = star;
	if (star->onDeath)
	{
		std::cout << "Call onDeath\n";
		star->onDeath();
	}
	else if (star->shell)
	{
		Shell::global = star->shell;
		std::cout << "Call Burst\n";
		star->shell->burst();
		delete star->shell;
	}
	pool->push_back(star);
}

void Star::free()
{
	for (std::list<Star*>::iterator it = active->begin(); it != active->end(); it++)
	{
		delete* it;
	}

	for (std::list<Star*>::iterator it = pool->begin(); it != pool->end(); it++)
	{
		delete* it;
	}
}

Spark* Spark::add(const float& x, const float& y, const Color& color, const float& angle, const float& speed, const float& life)
{
	Spark* instance;

	if (!pool->empty())
	{
		instance = pool->back();
		pool->pop_back();
	}
	else
	{
		instance = new Spark();
	}

	instance->x = x;
	instance->y = y;
	instance->preX = x;
	instance->preY = y;
	instance->color = color;
	instance->speedX = sinf(angle) * speed;
	instance->speedY = cosf(angle) * speed;
	instance->life = life;

	active->push_back(instance);
	return instance;
}

void Spark::returnInstance(Spark* const spark)
{
	pool->push_back(spark);
}

void Spark::free()
{
	for (std::list<Spark*>::iterator it = active->begin(); it != active->end(); it++)
	{
		delete* it;
	}

	for (std::list<Spark*>::iterator it = pool->begin(); it != pool->end(); it++)
	{
		delete* it;
	}
}

Shell::Shell(const ShellConfiguration& config) :
	comet(nullptr)
{
	starLifeVariation = config.starLifeVariation || 0.125f;
	color = config.color;
	glitterColor = config.glitterColor;
	starLife = config.starLife;
	starCount = config.starCount;
	spreadSize = config.spreadSize;
	glitter = config.glitter;
	pistil = config.pistil;
	pistilColor = config.pistilColor;
	streamers = config.streamers;
	crossette = config.crossette;
	floral = config.floral;
	crackle = config.crackle;
	horseTail = config.horseTail;

	if (!starCount)
	{
		const float density = config.starDensity || 1;
		const float scaledSize = spreadSize / 54.f;
		starCount = (int)fmaxf(6, scaledSize * scaledSize * density);
	}
}

void Shell::launch(const float& launchWidth, const float& launchHeight)
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

	this->comet = comet;
	this->comet->shell = this;

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

	/*if (Utility::rFloat() > 0.4f)
	{
		comet->haveSecondColor = true;
		comet->secondColor = Color::Invisible;
		comet->transitionTime = powf(Utility::rFloat(), 1.5f) * .7f + .5f;
	}*/


}

void Shell::burst()
{
	switch (Shell::global->glitter)
	{
	case Glitter::light:
		global_sparkFreq = 0.4f;
		global_sparkSpeed = 0.3f;
		global_sparkLife = 0.3f;
		global_sparkLifeVariation = 2.f;
		break;
	case Glitter::medium:
		global_sparkFreq = 0.2f;
		global_sparkSpeed = 0.44f;
		global_sparkLife = 0.7f;
		global_sparkLifeVariation = 2.f;
		break;
	case Glitter::heavy:
		global_sparkFreq = 0.08f;
		global_sparkSpeed = 0.8f;
		global_sparkLife = 1.4f;
		global_sparkLifeVariation = 2.f;
		break;
	case Glitter::thick:
		global_sparkFreq = 0.016f;
		global_sparkSpeed = 1.65f;
		global_sparkLife = 1.4f;
		global_sparkLifeVariation = 3.f;
		break;
	case Glitter::streamer:
		global_sparkFreq = 0.032f;
		global_sparkSpeed = 1.05f;
		global_sparkLife = 0.62f;
		global_sparkLifeVariation = 2.f;
		break;
	case Glitter::willow:
		global_sparkFreq = 0.12f;
		global_sparkSpeed = 0.34f;
		global_sparkLife = 1.4f;
		global_sparkLifeVariation = 3.8f;
		break;
	default:
		break;
	}

	global_sparkFreq /= 3.f;

	auto particleFactory = [](const float& anlge, const float& speedMult)
	{
		const float speed = Shell::global->spreadSize / 96;

		const float standardInitialSpeed = 700.f / 1800.f;

		Star* star = Star::add(
			Star::global->x,
			Star::global->y,
			Color::random(),
			anlge,
			speedMult * speed,
			Shell::global->starLife + Utility::rFloat() * Shell::global->starLifeVariation,
			Shell::global->horseTail ? Shell::global->comet && Shell::global->comet->speedX : 0,
			Shell::global->horseTail ? Shell::global->comet && Shell::global->comet->speedY : standardInitialSpeed
		);

		if (Shell::global->haveSecondColor)
		{
			star->transitionTime = Shell::global->starLife * (Utility::rFloat() * 0.05f + 0.32f);
			star->secondColor = Shell::global->secondColor;
		}

		

		if (Shell::global->crossette)
		{
			star->onDeath = crossetteEffect;
		}
		else if (Shell::global->crackle)
		{
			star->onDeath = crackleEffect;
		}
		else if (Shell::global->floral)
		{
			star->onDeath = floralEffect;
		}
		else if (Shell::global->fallingLeaves)
		{
			star->onDeath = fallingLeavesEffect;
		}

	};

	createBurst(30, particleFactory);
}
