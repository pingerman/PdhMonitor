#include "Task.h"

namespace Task
{
	void TaskManager::Start() 
	{
		//загрузка графиков ядер процессора:

		SYSTEM_INFO systemInfo;
		GetSystemInfo(&systemInfo);
		processorsCount = systemInfo.dwNumberOfProcessors;

		workers.assign(processorsCount, Worker(10));

		for (int i = 0; i < processorsCount; i++)
		{
			workers[i].Start(i);
		}

		renders.assign(processorsCount, Render());

		//настройка расцветки графиков:

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

		//загрузка измерительной сетки:
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
		//Проводим расчеты в отдельных потоках
		for (int i = 0; i < processorsCount; i++)
		{
			std::thread process(&TaskManager::AsyncUpdate, this, i);

			if(process.joinable())
				process.join();
		}

		//Визуализируем графики уже в основном потоке
		for (int i = 0; i < processorsCount; i++)
		{
			renders[i].VAOUpdate();
		}

		Visualize();
	}

	void TaskManager::Visualize()
	{
		openGL.GLRenderStart();

		//отрисовываем шкалу
		for (int i = 0; i < gridCount; i++)
		{
			gridRenders[i].Draw();
		}

		//отрисовываем графики
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