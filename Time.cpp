#include "Time.hpp"


Time::Time() {}

Time Time::_timeInstance;

Time& Time::Instance()
{
	return _timeInstance;
}

void Time::UpdateTime()
{
	_frameCount++;
	_prevFrameTime = _currFrameTime;
	_currFrameTime = SDL_GetTicks();
	_deltaTime = (_currFrameTime - _prevFrameTime) / 1000.0f;
}

Uint64 Time::CurrFrame()
{
	return _frameCount;
}

float Time::DeltaTime()
{
	return _deltaTime;
}
