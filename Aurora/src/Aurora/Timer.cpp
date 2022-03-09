#include<Aurora/Timer.hpp>

Timer::Timer():
	curTime(0),timeLimit(0)
{
	
}

Timer::Timer(const float& timeLimit):
	timeLimit(timeLimit),curTime(0)
{

}

void Timer::update()
{
	curTime += Graphics::getDeltaTime();
}

bool Timer::reached()
{
	return curTime >= timeLimit;
}

void Timer::restart()
{
	curTime = 0;
}

void Timer::setTimeLimit(const float& timeLimit)
{
	this->timeLimit = timeLimit;
}
