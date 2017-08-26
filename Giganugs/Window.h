#pragma once
#include <string>
#include <windows.h>

class Window
{

private: 
	HINSTANCE hInstance;
	HWND hwnd;
	std::wstring applicationName;


public:
	Window(int width, int height, const std::wstring& windowName);
	~Window();

	LRESULT MessagePump(UINT message, WPARAM wparam, LPARAM lparam);
};

