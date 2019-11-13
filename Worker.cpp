#include "Task.h"

namespace Task
{

	void Worker::Start(int processorNumber)
	{
		//Open the pdh query and getting system data:

		pdhStatus = PdhOpenQuery(NULL, 0, &hQuery);
		if (pdhStatus != ERROR_SUCCESS)
			return;

		TCHAR szObjectName[1024], szCounterName[1024], szCounterPath[1024], szMachineName[1024];
		DWORD dwSize = sizeof(szObjectName);
		DWORD dwPathSize = sizeof(szCounterPath);

		pdhStatus = PdhLookupPerfNameByIndex(NULL, 234, szObjectName, &dwSize);

		dwSize = sizeof(szCounterName);
		pdhStatus = PdhLookupPerfNameByIndex(NULL, 200, szCounterName, &dwSize);

		dwSize = sizeof(szMachineName);
		GetComputerName(szMachineName, &dwSize);

		//Getting the list of current cores:

		LPTSTR      szCountersBuf = NULL;
		DWORD       dwCountersSize = 0;
		LPTSTR      szInstancesBuf = NULL;
		DWORD       dwInstancesSize = 0;

		pdhStatus = PdhEnumObjectItems(NULL, szMachineName, szObjectName, 
											 szCountersBuf, &dwCountersSize, 
											 szInstancesBuf, &dwInstancesSize, 
											 PERF_DETAIL_WIZARD, 0);

		if (dwCountersSize) {
			szCountersBuf = (LPTSTR)malloc(dwCountersSize * sizeof(TCHAR));
			if (szCountersBuf == NULL) {
				return;
			}
		}
		else
			szCountersBuf = NULL;

		if (dwInstancesSize) {
			szInstancesBuf = (LPTSTR)malloc(dwInstancesSize * sizeof(TCHAR));
			if (szInstancesBuf == NULL) {
				free(szCountersBuf);
				return;
			}
		}
		else
			szInstancesBuf = NULL;

		pdhStatus = PdhEnumObjectItems(NULL, szMachineName, szObjectName,
			szCountersBuf, &dwCountersSize,
			szInstancesBuf, &dwInstancesSize,
			PERF_DETAIL_WIZARD, 0);

		//Formation of the path to the counter:

		LPTSTR currentCore = szInstancesBuf + (processorNumber * (lstrlen(szInstancesBuf) + 1));

		TCHAR* processor = currentCore; // _Total is already on the list

		  //Parameters of counter path: { szMachineName, szObjectName, szInstanceName, szParentInstance, dwInstanceIndex, szCounterName }
		PDH_COUNTER_PATH_ELEMENTS pe = { szMachineName, szObjectName, processor, NULL, 0, szCounterName };

		pdhStatus = PdhMakeCounterPath(&pe, szCounterPath, &dwPathSize, 0);

		pdhStatus = PdhAddCounter(hQuery, szCounterPath, 0, &hCounter);

		delete szCountersBuf;
		delete szInstancesBuf;
	}

	void Worker::Check()
	{
		PdhCollectQueryData(hQuery);
		PdhGetFormattedCounterValue(hCounter, PDH_FMT_LONG, NULL, &counterValue);
	}

	float Worker::GetCounterValue()
	{
		return pdhStatus != ERROR_SUCCESS ? 0.0f : ((float)counterValue.longValue) / 100.0f;
	}

	void Worker::Update()
	{
		updateCounter += timeManager.DeltaTime();
		if (updateCounter >= updateInterval)
		{
			updateCounter = 0;
			Check();

			data.Push(new float((float)GetCounterValue()));
		}
	}

	float** Worker::GetValues(int& count)
	{
		return data.Read(count);
	}

	void Worker::Close()
	{
		if (hCounter == nullptr || hQuery == nullptr)
			return;

		PdhRemoveCounter(hCounter);
		PdhCloseQuery(hQuery);
	}

	Worker::Worker()
	{
		Worker(100);
	}

	Worker::Worker(int updateInterval)
	{
		this->updateInterval = updateInterval;
		this->updateCounter = updateInterval + 1;
	}

	Worker::~Worker()
	{
		Close();
	}
}