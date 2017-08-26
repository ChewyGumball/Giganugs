#pragma once
#include <string>
#include <windows.h>

class Window
{

private: 
	HINSTANCE instance;
	HWND windowHandle;
	std::wstring applicationName;


public:
	Window(int width, int height, const std::wstring& windowName, int showState = SW_SHOW);
	~Window();

	LRESULT MessagePump(UINT message, WPARAM wparam, LPARAM lparam);
};

