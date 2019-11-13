#define _CRT_SECURE_NO_WARNINGS

#ifndef TASK_H
#define TASK_H

#include <thread>
#include <vector>
#include "OpenGL.h"
#include "Worker.h"
#include "Render.h"

namespace Task 
{
	class TaskManager
	{
	private:
		std::vector<Worker*> workers;
		std::vector<Render*> renders;
		std::vector<Render*> gridRenders;

		int processorsCount = 0;
		int gridCount = 0;

		void Visualize();
		void AsyncUpdate(int coreIndex);

	public:

		void Start();
		void Update();
		void Close();
	};

}

extern Task::TaskManager task;

#endif
