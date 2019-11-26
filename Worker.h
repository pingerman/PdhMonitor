#define _CRT_SECURE_NO_WARNINGS

#ifndef WORKER_H
#define WORKER_H

#include <Windows.h>
#include <iostream>
#include <Pdh.h>
#include <PdhMsg.h>
#include "Time.h"
//#include "Container.h"
#include "RingContainer.h"

#pragma comment(lib, "pdh.lib")

#include "Debug.h"
using namespace Debug;

namespace Task
{
	class IWorker
	{
	public:
		virtual void Start(int procNumber) {}
		virtual void Update() {}
		/*virtual float** GetValues(int& count) { return nullptr; }*/
		virtual std::shared_ptr<float> GetValues(int& count) { return nullptr; }
		virtual void Close() {}

		IWorker() {}
		IWorker(int dataCount, int updateInterval) {}
	};

	class Worker : public IWorker
	{
	private:
		HQUERY hQuery = nullptr;
		PDH_HCOUNTER hCounter = nullptr;
		PDH_STATUS pdhStatus = 0L;
		PDH_FMT_COUNTERVALUE counterValue = { 0 };
		int updateInterval = 10;
		int updateCounter = 11;

		//Containers::Container<float> data;
		std::unique_ptr<Containers::RingContainer<float>> data;

		int count;
		int increment = 0;
		float* arr;

		void Check();
		float GetCounterValue();

	public:

		void Start(int procNumber) override;
		void Update() override;
		/*float** GetValues(int& count) override;*/
		std::shared_ptr<float> GetValues(int& count) override;
		void Close() override;

		Worker();
		Worker(int dataCount, int updateInterval);

		~Worker();
	};

}

#endif
