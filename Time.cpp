#include "Time.h"

namespace Time
{
	void TimeManager::Update()
	{
		clock_t currentTime = clock();
		if (currentTime > timer)
		{
			deltaTime = currentTime - timer;
			timer = currentTime;
		}
	}

	clock_t TimeManager::DeltaTime()
	{
		return deltaTime;
	}

	float TimeManager::ScaledDeltaTime()
	{
		return (float)deltaTime * scale;
	}

	TimeManager::TimeManager() 
	{
		TimeManager(1.0f);
	}

	TimeManager::TimeManager(float scale)
	{
		this->scale = scale;
	}
}