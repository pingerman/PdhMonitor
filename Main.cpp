#define _CRT_SECURE_NO_WARNINGS

#include "OpenGL.h"
#include "Task.h"

using namespace OGL;
using namespace Task;

//-----WinAPI Функции-----//
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void AppRun();

//-----Глобальные переменные-----//
HWND hWnd;

TaskManager task;
OpenGL openGL;
Time::TimeManager timeManager;

//Точка входа WinAPI
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{

	WNDCLASS wc = {};

	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WindowProc;
	wc.hInstance = hInstance;
	wc.lpszClassName = L"TestClass";

	if (!RegisterClass(&wc))
		return 0;

	hWnd = CreateWindow(wc.lpszClassName, L"TestWindow", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, WIN_WIDTH, WIN_HEIGHT, NULL, NULL, wc.hInstance, NULL);

	if (hWnd == NULL)
		return 0;

	//Инициализация OpenGL
	if (!openGL.GLInit(hWnd))
	{
		openGL.GLClear();
		openGL.GLClose();
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	task.Start();
	
	//Главный цикл приложения
	AppRun();

	//Закрытие
	task.Close();
	openGL.GLClear();
	openGL.GLClose();

	return 0;
}

//Обработчик сообщений WinAPI
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		return 0;
	}
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

//Главный цикл приложения
void AppRun()
{
	MSG msg = {};

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		timeManager.Update();
		task.Update();
	}
}