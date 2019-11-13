#include "Task.h"

namespace Task
{
	void TaskManager::Start() 
	{
		//Load the graphs of processors cores:

		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		processorsCount = systemInfo.dwNumberOfProcessors;

		workers.assign(processorsCount, Worker(10));

		for (int i = 0; i < processorsCount; i++)
		{
			workers[i].Start(i);
		}

		renders.assign(processorsCount, Render());

		//Setting the colors of graphs:

		float color[6][3] = {{1.0f, 0.0f, 0.0f},
							 {0.0f, 1.0f, 0.0f},
							 {0.0f, 0.0f, 1.0f}, 
							 {0.0f, 1.0f, 1.0f},
							 {1.0f, 0.0f, 1.0f},
							 {1.0f, 1.0f, 0.0f}};

		int colorsCount = 6;

		for (int i = 0, j = 0; i < processorsCount; i++, j++)
		{
			renders[i].Load();
			renders[i].SetColor(&color[j][0]);

			if (j >= colorsCount)
				j = 0;
		}

		//Load measuring grid:
		gridCount = 11;

		gridRenders.assign(gridCount, Render());

		float gridColor[3] = { 0.6f, 0.6f, 0.6f };

		for (int i = 0, j = 0; i < gridCount; i++, j++)
		{
			gridRenders[i].Load();
			gridRenders[i].SetColor(&gridColor[0]);

			float gridValue = (0.1f * i);

			gridRenders[i].Update(gridValue);
		}
	}

	void TaskManager::AsyncUpdate(int coreIndex)
	{
		workers[coreIndex].Update();

		int count = 0;
		float** arrValues = workers[coreIndex].GetValues(count);

		renders[coreIndex].Update(arrValues, &count);
	}

	void TaskManager::Update()
	{
		//Calculations in separates threads
		for (int i = 0; i < processorsCount; i++)
		{
			std::thread process(&TaskManager::AsyncUpdate, this, i);

			if(process.joinable())
				process.join();
		}

		//Visualize the graphs in the main thread
		for (int i = 0; i < processorsCount; i++)
		{
			renders[i].VAOUpdate();
		}

		Visualize();
	}

	void TaskManager::Visualize()
	{
		openGL.GLRenderStart();

		//Visualize the meausing grid
		for (int i = 0; i < gridCount; i++)
		{
			gridRenders[i].Draw();
		}

		//Visualize the graphs
		for (int i = 0; i < processorsCount; i++)
		{
			renders[i].Draw();
		}

		openGL.GLRenderEnd();
	}

	void TaskManager::Close()
	{
		for (int i = 0; i < processorsCount; i++)
		{
			workers[i].Close();
			renders[i].Clear();
		}

		for (int i = 0; i < gridCount; i++)
		{
			gridRenders[i].Clear();
		}
	}
}