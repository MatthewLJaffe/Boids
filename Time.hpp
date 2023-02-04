#pragma once
#include <cstdint>
#include<SDL.h>

class Time
{
public:
	static Time& Instance();
	float DeltaTime();
	Uint64 CurrFrame();
	void UpdateTime();
	Time(const Time&) = delete;
private:
	float _deltaTime = 0;
	Uint32 _currFrameTime = 0;
	Uint32 _prevFrameTime = 0;
	Uint64 _frameCount = 0;
	static Time _timeInstance;
	Time();
};
