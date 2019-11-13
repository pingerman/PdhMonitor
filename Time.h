#ifndef TIME_H
#define TIME_H

#include <time.h>

namespace Time
{
	class TimeManager
	{
	private:
		clock_t timer;
		clock_t deltaTime;
		float scale;

	public:

		void Update();
		clock_t DeltaTime();
		float ScaledDeltaTime();

		TimeManager();
		TimeManager(float scale);
	};
}

extern Time::TimeManager timeManager;

#endif
